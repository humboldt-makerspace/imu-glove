#ifndef UDP_MANAGER_HPP
#define UDP_MANAGER_HPP

#include "constants.h"
#include "Arduino.h"
#include "WiFiUdp.h"

class UDPManager {
private:
	/* functions */

public:
	/* variables */
	static WiFiUDP UDPServer;
	static uint8_t packetBuffer[MAX_PACKET_SIZE];

	/* functions */
	static String readPackage (void);
	static void sendPackage (String msg, const char* host, uint16_t port);
	static void processCommand (String cmd);
};

#endif
