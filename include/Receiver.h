#ifndef RECEIVER_H
# define RECEIVER_H

# include "comms.h"
# include "esp_now.h"

# include <freertos/FreeRTOS.h>
# include <stdint.h>

class Receiver {
  public:
	Receiver();
	~Receiver();

	esp_err_t init();

	bool     getLastPacket(t_ctrl_pckt& out) const;
	bool     isLinkAlive() const;
	uint32_t getLostPackets() const;

	static constexpr uint32_t LINK_TIMEOUT_MS = 300; // Para ativar failsafe

  private:
	// O ESP-NOW exige callback sem `this`, portanto precisa ser static.
	static void onReceived(const esp_now_recv_info_t *info, const uint8_t *incomingData, int len);

	void handlePacket(const t_ctrl_pckt& pckt);

	static Receiver *s_instance;

	t_ctrl_pckt          m_last;
	uint32_t             m_lastPacketMs;
	uint32_t             m_lostPackets;
	uint16_t             m_lastPacketId;
	bool                 m_hasPacket;
	mutable portMUX_TYPE m_mux;
};

#endif // RECEIVER_H
