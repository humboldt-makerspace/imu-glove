#include "includes.h"

void setup ()
{
	Setup::init();
}

void loop ()
{
	Interface::readButtons();
	Orientation::updateOrientation();
	Action::detectHandGesture();
	Control::sendCommand();
	//IMU::showData();
	Orientation::showOrientation();
	//Interface::leds[0] = CRGB::Green;
	FastLED.show();
}

