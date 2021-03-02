#include "sensor/Calibration.hpp"
#include "system/Interface.hpp"

CalibData Calibration::data;

void Calibration::showCalibrationData (void)
{
	Serial.println("Calibration data:");

	Serial.print("Gyro offsets: x: ");
	Serial.print(Calibration::data.gyrOffset.x);
	Serial.print(" y: ");
	Serial.print(Calibration::data.gyrOffset.y);
	Serial.print(" z: ");
	Serial.println(Calibration::data.gyrOffset.z);

	Serial.print("Threshold: ");
	Serial.println(Calibration::data.gyrThreshold);

	Serial.print("Acc offsets: x: ");
	Serial.print(Calibration::data.accOffset.x);
	Serial.print(" y: ");
	Serial.print(Calibration::data.accOffset.y);
	Serial.print(" z: ");
	Serial.println(Calibration::data.accOffset.z);

	Serial.print("Acc factors: x: ");
	Serial.print(Calibration::data.accFactor.x);
	Serial.print(" y: ");
	Serial.print(Calibration::data.accFactor.y);
	Serial.print(" z: ");
	Serial.println(Calibration::data.accFactor.z);
}

void Calibration::performCalibration (void)
{
	unsigned long calibTime;
	Serial.println("Starting imu calibration ...");

	Interface::leds[1] = CRGB::Red;
	FastLED.show();

	delay(2000);
	Serial.println("Calibrating gyroscope, please hold still");

	V3 measGyr = {
		.x = 0.0,
		.y = 0.0,
		.z = 0.0
	};

	V3 minMeas = {
		.x = 20.0,
		.y = 20.0,
		.z = 20.0
	};

	V3 maxMeas = {
		.x = -20.0,
		.y = -20.0,
		.z = -20.0
	};

	int samples = 0;
	calibTime = millis();
	while (millis() - calibTime < GYRO_CALIB_TIME) {
		IMU::read(false);
		measGyr.x += IMU::gyr.x;
		measGyr.y += IMU::gyr.y;
		measGyr.z += IMU::gyr.z;
		if (IMU::gyr.x > maxMeas.x) maxMeas.x = IMU::gyr.x;
		if (IMU::gyr.y > maxMeas.y) maxMeas.y = IMU::gyr.y;
		if (IMU::gyr.z > maxMeas.z) maxMeas.z = IMU::gyr.z;
		if (IMU::gyr.x < minMeas.x) minMeas.x = IMU::gyr.x;
		if (IMU::gyr.y < minMeas.y) minMeas.y = IMU::gyr.y;
		if (IMU::gyr.z < minMeas.z) minMeas.z = IMU::gyr.z;
		samples++;
		IMU::showData();
	}

	measGyr.x /= samples;
	measGyr.y /= samples;
	measGyr.z /= samples;

	Calibration::data.gyrOffset.x = measGyr.x;
	Calibration::data.gyrOffset.y = measGyr.y;
	Calibration::data.gyrOffset.z = measGyr.z;

	Calibration::data.gyrThreshold = max(
		max(max(measGyr.x - minMeas.x, measGyr.y - minMeas.y), measGyr.z - minMeas.z),
		max(max(maxMeas.x - measGyr.x, maxMeas.y - measGyr.y), maxMeas.z - measGyr.z)
	) + GYR_THRESHOLD_TOLERANCE;

	minMeas = {
		.x = 20.0,
		.y = 20.0,
		.z = 20.0
	};

	maxMeas = {
		.x = -20.0,
		.y = -20.0,
		.z = -20.0
	};

	Serial.println("Calibrating accelerometer, please align the sensor axes with gravity");

	// Interface::leds[1] = CRGB::Yellow;
	// FastLED.show();

	// calibTime = millis();
	// while (millis() - calibTime < ACC_CALIB_TIME) {
	// 	IMU::read(false);
	// 	if (IMU::acc.x > maxMeas.x) maxMeas.x = IMU::acc.x;
	// 	if (IMU::acc.y > maxMeas.y) maxMeas.y = IMU::acc.y;
	// 	if (IMU::acc.z > maxMeas.z) maxMeas.z = IMU::acc.z;
	// 	if (IMU::acc.x < minMeas.x) minMeas.x = IMU::acc.x;
	// 	if (IMU::acc.y < minMeas.y) minMeas.y = IMU::acc.y;
	// 	if (IMU::acc.z < minMeas.z) minMeas.z = IMU::acc.z;
	// 	IMU::showData();
	// }
	// Calibration::data.accFactor.x = 2.0 / (maxMeas.x - minMeas.x);
	// Calibration::data.accFactor.y = 2.0 / (maxMeas.y - minMeas.y);
	// Calibration::data.accFactor.z = 2.0 / (maxMeas.z - minMeas.z);

	// Calibration::data.accOffset.x = Calibration::data.accFactor.x * (maxMeas.x + minMeas.x) / 2;
	// Calibration::data.accOffset.y = Calibration::data.accFactor.y * (maxMeas.y + minMeas.y) / 2;
	// Calibration::data.accOffset.z = Calibration::data.accFactor.z * (maxMeas.z + minMeas.z) / 2;

	Calibration::data.accFactor.x = 2.0 / (MAX_ACC_X - MIN_ACC_X);
	Calibration::data.accFactor.y = 2.0 / (MAX_ACC_Y - MIN_ACC_Y);
	Calibration::data.accFactor.z = 2.0 / (MAX_ACC_Z - MIN_ACC_Z);

	Calibration::data.accOffset.x = Calibration::data.accFactor.x * (MAX_ACC_X + MIN_ACC_X) / 2;
	Calibration::data.accOffset.y = Calibration::data.accFactor.y * (MAX_ACC_Y + MIN_ACC_Y) / 2;
	Calibration::data.accOffset.z = Calibration::data.accFactor.z * (MAX_ACC_Z + MIN_ACC_Z) / 2;

	showCalibrationData();
	Serial.println("Finished calibrating");

	Interface::leds[1] = CRGB::Green;
	FastLED.show();

	delay(2000);

	Interface::leds[1] = CRGB::Black;
	FastLED.show();

	UserPrefs::saveValuesToEEPROM();
}
