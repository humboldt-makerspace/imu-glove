#include "features/Control.hpp"
#include "system/Interface.hpp"

bool Control::enableCommands = false;

void Control::sendCommand (void)
{
	if (!Control::enableCommands) return;
	switch (Action::currentGesture) {
		case Z_SIDE: {
			UDPManager::sendPackage(String("/color 0,255,0"), LED_WALL_HOST, 2808);
			break;
		}
		case Z_UP: {
			UDPManager::sendPackage(String("/color rainbowh"), LED_WALL_HOST, 2808);
			break;
		}
		case Z_DOWN: {
			UDPManager::sendPackage(String("/color 255,0,0"), LED_WALL_HOST, 2808);
			break;
		}
		case X_SIDE: {
			UDPManager::sendPackage(String("/color 0,0,255"), LED_WALL_HOST, 2808);
			break;
		}
		case X_UP: {
			UDPManager::sendPackage(String("/mode matrix"), LED_WALL_HOST, 2808);
			break;
		}
		case X_DOWN: {
			UDPManager::sendPackage(String("/mode network"), LED_WALL_HOST, 2808);
			break;
		}
		default: {
			break;
		}
	}
}
