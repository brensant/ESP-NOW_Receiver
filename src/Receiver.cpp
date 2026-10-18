#include "Receiver.h"

#include <Arduino.h>
#include <string.h>

Receiver* Receiver::s_instance = nullptr;

/********************************* LIFECYCLE **********************************/

Receiver::Receiver()
  : m_last()
  , m_lastPacketMs(0)
  , m_lostPackets(0)
  , m_lastPacketId(0)
  , m_hasPacket(false)
{
	portMUX_INITIALIZE(&m_mux);
}

Receiver::~Receiver()
{
	if (s_instance == this)
		s_instance = nullptr;
}

/************************** STATIC MEMBER FUNCTIONS ***************************/

void Receiver::onReceived(const esp_now_recv_info_t *info, const uint8_t *incomingData, int len)
{
	static const uint8_t emitter[] = EMITTER_MAC;

	if (!s_instance)
		return;
	if (len != sizeof(t_ctrl_pckt))
		return;
	if (memcmp(info->src_addr, emitter, ESP_NOW_ETH_ALEN) != 0)
		return;

	t_ctrl_pckt pckt;
	memcpy(&pckt, incomingData, sizeof pckt);

	s_instance->handlePacket(pckt);
}

/************************ NON-STATIC MEMBER FUNCTIONS *************************/

/*
 * Inicializa o ESP-NOW. Chamar depois de `WiFi.mode(WIFI_STA)`.
 */
esp_err_t Receiver::init()
{
	s_instance = this;

	if (esp_now_init() != ESP_OK) {
		Serial.println("Erro ao inicializar o ESP-NOW");
		return (ESP_FAIL);
	}

	if (esp_now_register_recv_cb(onReceived) != ESP_OK) {
		esp_now_deinit();
		Serial.println("Erro ao registrar callback do receptor");
		return (ESP_FAIL);
	}

	return (ESP_OK);
}

/**
 * Copia o último pacote válido para `out`. Retorna false se ainda não chegou nenhum.
 */
bool Receiver::getLastPacket(t_ctrl_pckt& out) const
{
	bool hasPacket;

	portENTER_CRITICAL(&m_mux);
	hasPacket = m_hasPacket;
	if (hasPacket)
		out = m_last;
	portEXIT_CRITICAL(&m_mux);

	return (hasPacket);
}

bool Receiver::isLinkAlive() const
{
	bool     hasPacket;
	uint32_t lastPacketMs;

	portENTER_CRITICAL(&m_mux);
	hasPacket  = m_hasPacket;
	lastPacketMs = m_lastPacketMs;
	portEXIT_CRITICAL(&m_mux);

	return (hasPacket && (millis() - lastPacketMs) < LINK_TIMEOUT_MS);
}

uint32_t Receiver::getLostPackets() const
{
	uint32_t lostPackets;

	portENTER_CRITICAL(&m_mux);
	lostPackets = m_lostPackets;
	portEXIT_CRITICAL(&m_mux);

	return (lostPackets);
}

/****************************** HELPER FUNCTIONS ******************************/

/**
 * Roda na task do Wi-Fi: manter curto, sem Serial.
 */
void Receiver::handlePacket(const t_ctrl_pckt& pckt)
{
	uint32_t now = millis();

	portENTER_CRITICAL(&m_mux);

	if (m_hasPacket) {
		int16_t delta = (int16_t)(pckt.packetId - m_lastPacketId);

		// Duplicado ou levemente fora de ordem: descarta.
		// Um salto negativo grande indica reinício do emissor: aceita e ressincroniza.
		if (delta == 0 || (delta < 0 && delta > -8)) {
			portEXIT_CRITICAL(&m_mux);
			return;
		}
		if (delta > 1)
			m_lostPackets += delta - 1;
	}

	m_last         = pckt;
	m_lastPacketId = pckt.packetId;
	m_lastPacketMs = now;
	m_hasPacket    = true;

	portEXIT_CRITICAL(&m_mux);
}
