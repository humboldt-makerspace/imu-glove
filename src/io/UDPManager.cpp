#include "io/UDPManager.hpp"
#include "system/Interface.hpp"

WiFiUDP UDPManager::UDPServer;
uint8_t UDPManager::packetBuffer[MAX_PACKET_SIZE];

String UDPManager::readPackage (void)
{
	String myData = "";
	int cb = UDPManager::UDPServer.parsePacket();
	if (cb) {
		for (int i = 0; i < MAX_PACKET_SIZE; i++) packetBuffer[i] = 0;
		UDPManager::UDPServer.read(packetBuffer, cb);
		for (int i = 0; i < cb; i++) {
			myData += (char)packetBuffer[i];
		}
	}
	return myData;
}

void UDPManager::sendPackage (String msg, const char* host, uint16_t port)
{
	UDPManager::UDPServer.beginPacket(host, port);
    UDPManager::UDPServer.write(msg.c_str());
    UDPManager::UDPServer.endPacket();
}

void UDPManager::processCommand (String cmd)
{
	if (cmd.isEmpty()) return;
	cmd.toLowerCase();

}
