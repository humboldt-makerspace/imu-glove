#include "sensor/UserPrefs.hpp"
#include "system/Interface.hpp"

void UserPrefs::saveValuesToEEPROM (void)
{
	Serial.println("Saved values to EEPROM");
	uint addr = 0;
	EEPROM.begin(EEPROM_SIZE);
  	EEPROM.put(addr, Calibration::data);
	EEPROM.commit();
}

void UserPrefs::readValuesFromEEPROM (void)
{
	Serial.println("Reading from EEPROM");
	uint addr = 0;
	EEPROM.begin(EEPROM_SIZE);
  	EEPROM.get(addr, Calibration::data);
}

void UserPrefs::clearEEPROM (void)
{
	Serial.println("Clearing EEPROM");
	EEPROM.begin(EEPROM_SIZE);
	for (int i = 0; i < EEPROM_SIZE; i++) EEPROM.write(i, 0);
	EEPROM.end();
}

void UserPrefs::resetEEPROM (void)
{
	Serial.println("Resetting EEPROM");
	CalibData c;
	c.accFactor.x = 1.0;
	c.accFactor.y = 1.0;
	c.accFactor.z = 1.0;
	c.accOffset.x = 0.0;
	c.accOffset.y = 0.0;
	c.accOffset.z = 0.0;
	c.gyrOffset.x = 0.0;
	c.gyrOffset.y = 0.0;
	c.gyrOffset.z = 0.0;
	c.gyrThreshold = 0.0;

	uint addr = 0;
	EEPROM.begin(EEPROM_SIZE);
	EEPROM.put(addr, c);
	EEPROM.commit();
}
