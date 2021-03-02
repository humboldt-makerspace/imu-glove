#include "sensor/IMU.hpp"
#include "system/Interface.hpp"

V3 IMU::acc;
V3 IMU::gyr;
unsigned long IMU::sleepTimer;

void I2C_Write (uint8_t deviceAddress, uint8_t regAddress, uint8_t data)
{
	Wire.beginTransmission(deviceAddress);
	Wire.write(regAddress);
	Wire.write(data);
	Wire.endTransmission();
}

/* note: MPU Bit order is LSB, e.g. 1 is 00000001 */
void IMU::init (void)
{
	delay(150);
	I2C_Write(MPU6050_SLAVE_ADDRESS, MPU6050_REGISTER_SMPLRT_DIV, 0x07);
	I2C_Write(MPU6050_SLAVE_ADDRESS, MPU6050_REGISTER_PWR_MGMT_1, 0x01);
	I2C_Write(MPU6050_SLAVE_ADDRESS, MPU6050_REGISTER_PWR_MGMT_2, 0x00);
	I2C_Write(MPU6050_SLAVE_ADDRESS, MPU6050_REGISTER_CONFIG, 0x00);
	I2C_Write(MPU6050_SLAVE_ADDRESS, MPU6050_REGISTER_GYRO_CONFIG, 0x08);
	I2C_Write(MPU6050_SLAVE_ADDRESS, MPU6050_REGISTER_ACCEL_CONFIG, 0x08);
	I2C_Write(MPU6050_SLAVE_ADDRESS, MPU6050_REGISTER_FIFO_EN, 0x00);
	I2C_Write(MPU6050_SLAVE_ADDRESS, MPU6050_REGISTER_INT_ENABLE, 0x01);
	I2C_Write(MPU6050_SLAVE_ADDRESS, MPU6050_REGISTER_SIGNAL_PATH_RESET, 0x00);
	I2C_Write(MPU6050_SLAVE_ADDRESS, MPU6050_REGISTER_USER_CTRL, 0x00);
	IMU::sleepTimer = millis();
}

void IMU::read (bool calibrated)
{
	Wire.beginTransmission(MPU6050_SLAVE_ADDRESS);
	Wire.write(MPU6050_REGISTER_ACCEL_XOUT_H);
	Wire.endTransmission();
	Wire.requestFrom(MPU6050_SLAVE_ADDRESS, 14);

	int16_t accelX = (((int16_t)Wire.read() << 8) | Wire.read());
	int16_t accelY = (((int16_t)Wire.read() << 8) | Wire.read());
	int16_t accelZ = (((int16_t)Wire.read() << 8) | Wire.read());
	int16_t gyroX = (((int16_t)Wire.read() << 8) | Wire.read());
	gyroX = (((int16_t)Wire.read() << 8) | Wire.read());
	int16_t gyroY = (((int16_t)Wire.read() << 8) | Wire.read());
	int16_t gyroZ = (((int16_t)Wire.read() << 8) | Wire.read());

	double ax = (double)accelX / ACCEL_SCALE_FACTOR;
	double ay = (double)accelY / ACCEL_SCALE_FACTOR;
	double az = (double)accelZ / ACCEL_SCALE_FACTOR;
	double gx = (double)gyroX / GYRO_SCALE_FACTOR;
	double gy = (double)gyroY / GYRO_SCALE_FACTOR;
	double gz = (double)gyroZ / GYRO_SCALE_FACTOR;

	if (calibrated) {
		IMU::acc.x = ax * Calibration::data.accFactor.x - Calibration::data.accOffset.x;
		IMU::acc.y = ay * Calibration::data.accFactor.y - Calibration::data.accOffset.y;
		IMU::acc.z = az * Calibration::data.accFactor.z - Calibration::data.accOffset.z;
		IMU::gyr.x = gx - Calibration::data.gyrOffset.x;
		IMU::gyr.y = gy - Calibration::data.gyrOffset.y;
		IMU::gyr.z = gz - Calibration::data.gyrOffset.z;

		if (abs(IMU::gyr.x) < Calibration::data.gyrThreshold) IMU::gyr.x = 0.0;
		if (abs(IMU::gyr.y) < Calibration::data.gyrThreshold) IMU::gyr.y = 0.0;
		if (abs(IMU::gyr.z) < Calibration::data.gyrThreshold) IMU::gyr.z = 0.0;
	}
	else {
		IMU::acc.x = ax;
		IMU::acc.y = ay;
		IMU::acc.z = az;
		IMU::gyr.x = gx;
		IMU::gyr.y = gy;
		IMU::gyr.z = gz;
	}

	if (IMU::gyr.x != 0 || IMU::gyr.y != 0 || IMU::gyr.z != 0) IMU::sleepTimer = millis();
	if (millis() - IMU::sleepTimer > SLEEP_THRESHOLD) {
		I2C_Write(MPU6050_SLAVE_ADDRESS, MPU6050_REGISTER_PWR_MGMT_1, 0x40);
		Interface::goToSleep();
	}

	delay(10);
}

void IMU::showData (void)
{
	Serial.print("ACC: x: ");
	Serial.print(IMU::acc.x);
	Serial.print(" y: ");
	Serial.print(IMU::acc.y);
	Serial.print(" z: ");
	Serial.println(IMU::acc.z);

	Serial.print("GYR: x: ");
	Serial.print(IMU::gyr.x);
	Serial.print(" y: ");
	Serial.print(IMU::gyr.y);
	Serial.print(" z: ");
	Serial.println(IMU::gyr.z);
}
