#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "constants.h"
#include "Arduino.h"
#include <ESP8266WiFi.h>
#include "WiFiUdp.h"
#include "FastLED.h"
#include "Wire.h"

#include "io/Parser.hpp"
#include "io/UDPManager.hpp"
#include "sensor/Calibration.hpp"
#include "sensor/IMU.hpp"
#include "sensor/UserPrefs.hpp"
#include "utils/VecUtils.hpp"
#include "utils/Madgwick.hpp"
#include "utils/Action.hpp"
#include "utils/Orientation.hpp"
#include "custom.h"

#include "features/Control.hpp"

class Interface {
private:
	/* variables */
	static boolean buttons[NUM_BUTTONS];

	/* functions */

public:
	/* variables */
	static CRGB leds[NUM_LEDS];
	static bool btnPressed[NUM_BUTTONS];
	static unsigned long pressTime[NUM_BUTTONS];

	/* functions */
	static void goToSleep (void);
	static void readButtons (void);
};

#endif
