#ifndef CONSTANTS_H
#define CONSTANTS_H

/* WiFi and UDP */
#define MAX_PACKET_SIZE						100

/* time information */
#define TIME_ZONE							1
#define DST									1

/* buttons */
#define BUTTON_1_PIN						D5
#define BUTTON_2_PIN						D7
#define NUM_BUTTONS							2
#define LONG_PRESS_DURATION					2000

/* status leds */
#define LED_PIN								D6
#define NUM_LEDS							2

/* imu */
#define SDA_PIN								D1
#define SCL_PIN								D2

/* MPU6050 Slave Device Address */
#define MPU6050_SLAVE_ADDRESS				0x68

/* sensitivity scale factor respective to full scale setting provided in datasheet */
#define ACCEL_SCALE_FACTOR					8192.0
#define GYRO_SCALE_FACTOR					65.5

/* MPU6050 few configuration register addresses */
#define MPU6050_REGISTER_SMPLRT_DIV			0x19
#define MPU6050_REGISTER_USER_CTRL			0x6A
#define MPU6050_REGISTER_PWR_MGMT_1			0x6B
#define MPU6050_REGISTER_PWR_MGMT_2			0x6C
#define MPU6050_REGISTER_CONFIG				0x1A
#define MPU6050_REGISTER_GYRO_CONFIG		0x1B
#define MPU6050_REGISTER_ACCEL_CONFIG		0x1C
#define MPU6050_REGISTER_FIFO_EN			0x23
#define MPU6050_REGISTER_INT_ENABLE			0x38
#define MPU6050_REGISTER_ACCEL_XOUT_H		0x3B
#define MPU6050_REGISTER_SIGNAL_PATH_RESET	0x68

/* calibration parameters */
#define GYRO_CALIB_TIME						4000
#define ACC_CALIB_TIME						30000
#define GYR_THRESHOLD_TOLERANCE				0.2

#define MAX_ACC_X							1.06							
#define MAX_ACC_Y							1.01
#define MAX_ACC_Z							0.80
#define MIN_ACC_X							-0.96
#define MIN_ACC_Y							-1.00
#define MIN_ACC_Z							-1.26

/* EEPROM */
#define EEPROM_SIZE							128

/* madgwick filter */
#define MADGWICK_BETA						0.6
#define IT_COUNT							10

/* deep sleep */
#define SLEEP_THRESHOLD						30000

/* gestures */
#define DIRECTION_TOLERANCE					0.08
#define HOLD_TIME							1000

/* rc robot */
#define SPEED_FLATTEN_EXP					3.0
#define DEATH_ZONE							0.02
#define CMD_DRV								"/drive "
#define M_PI_2								1.570796326794896
#define M_PI								3.14159265358979

typedef enum directions {
	HORIZONTAL, UPWARDS, DOWNWARDS, UNKNOWN_DIRECTION
} Direction;

typedef enum gestures {
	DOWN_HOLD, UP_HOLD, X_SIDE, X_UP, X_DOWN, Y_SIDE, Y_UP, Y_DOWN, Z_SIDE, Z_UP, Z_DOWN, UNKNOWN_GESTURE
} Gesture;

#endif
