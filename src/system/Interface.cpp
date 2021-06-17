#include "system/Interface.hpp"

boolean Interface::buttons[NUM_BUTTONS];
bool Interface::btnPressed[NUM_BUTTONS];
unsigned long Interface::pressTime[NUM_BUTTONS];
CRGB Interface::leds[NUM_LEDS];

void Interface::goToSleep (void)
{
	for (int i = 0; i < NUM_LEDS; i++) {
		Interface::leds[i] = CRGB::Black;
	}
	FastLED.show();
	Serial.println("Going to sleep, wake me up with reset button");
	ESP.deepSleep(0);
}

void Interface::readButtons (void)
{
	buttons[0] = digitalRead(BUTTON_1_PIN);
	buttons[1] = digitalRead(BUTTON_2_PIN);

	for (int i = 0; i < NUM_BUTTONS; i++) {
		if (!buttons[i]) {
			if (pressTime[i] == LONG_MAX) {
				btnPressed[i] = true;
				pressTime[i] = millis();
			}
		}
	}
	if (btnPressed[0]) {
		if (buttons[0]) {
			if (pressTime[0] != LONG_MAX - 1) {
				btnPressed[0] = false;
				//IMU::recordRaw(true);
				Control::enableCommands = !Control::enableCommands;
				Interface::leds[1] = Control::enableCommands ? CRGB::Green : CRGB::Yellow;
				pressTime[0] = LONG_MAX;
			}
		}
		else if ((millis() > pressTime[0]) && (millis() - pressTime[0] > LONG_PRESS_DURATION)) {
			//Calibration::performCalibration();
			pressTime[0] = LONG_MAX - 1;
			btnPressed[0] = false;
		}
	}

	if (btnPressed[1]) {
		if (buttons[1]) {
			if (pressTime[1] != LONG_MAX - 1) {
				btnPressed[1] = false;
				//IMU::recordRaw(false);
				Control::switchHost();
				pressTime[1] = LONG_MAX;
			}
		}
		else if ((millis() > pressTime[1]) && (millis() - pressTime[1] > LONG_PRESS_DURATION)) {
			//UserPrefs::resetEEPROM();
			pressTime[1] = LONG_MAX - 1;
			btnPressed[1] = false;
		}
	}

	for (int i = 0; i < NUM_BUTTONS; i++) {
		if (buttons[i]) {
			pressTime[i] = LONG_MAX;
			btnPressed[i] = false;
		}
	}
}
