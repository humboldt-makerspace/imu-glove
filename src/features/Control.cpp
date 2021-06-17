#include "features/Control.hpp"
#include "system/Interface.hpp"

bool Control::enableCommands = false;
HostGadget Control::gadget = RC_ROBOT;

void Control::sendCommand (void)
{
	if (!Control::enableCommands) return;
	switch (Control::gadget) {
		case LED_WALL: {
			Control::ctrlLedWall();
			break;
		}
		case RC_ROBOT: {
			Control::ctrlRCRobot();
			break;
		}
		default: {
			break;
		}
	}
}

void Control::switchHost (void)
{
	if (Control::gadget == RC_ROBOT) Control::gadget = LED_WALL;
	else {
		int tmp = (int) Control::gadget;
		tmp++;
		Control::gadget = (HostGadget) tmp;
	}

	switch (Control::gadget) {
		case RC_ROBOT: {
			Interface::leds[0] = CRGB::Blue;
			break;
		}
		case LED_WALL: {
			Interface::leds[0] = CRGB::Red;
			break;
		}
		default: {
			break;
		}
	}
}

void Control::ctrlLedWall (void)
{
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

void Control::ctrlRCRobot (void)
{
	double angle = atan2(Orientation::orientation.x, Orientation::orientation.y);
	angle -= M_PI_2;
	if (angle < -M_PI) angle += 2 * M_PI;
	int degrees = (int)(angle * RAD_TO_DEG);
	double ampl = pow(sqrt(pow(Orientation::orientation.x, 2.0) + pow(Orientation::orientation.y, 2.0)), SPEED_FLATTEN_EXP);
	int speed = 0;
	if (ampl < DEATH_ZONE) speed = 0;
	else speed = (int)(ampl * 100.0);

	String degreesStr = String(degrees);
	String speedStr = String(speed);

	String drvCmd = CMD_DRV + degreesStr + "," + speedStr;
	Serial.print("sending out: ");
	Serial.print(degreesStr);
	Serial.print(", ");
	Serial.println(speedStr);

	UDPManager::sendPackage(drvCmd, RC_ROBOT_HOST, 2808);
}
