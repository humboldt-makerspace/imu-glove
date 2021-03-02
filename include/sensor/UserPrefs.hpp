#ifndef USER_PREFS_HPP
#define USER_PREFS_HPP

#include "EEPROM.h"
#include "Calibration.hpp"

class UserPrefs {
private:
	/* variables */

	/* functions */

public:
	/* variables */

	/* functions */
	static void saveValuesToEEPROM (void);
	static void readValuesFromEEPROM (void);
	static void clearEEPROM (void);
	static void resetEEPROM (void);
};

#endif
