#include "utils/Madgwick.hpp"
#include "system/Interface.hpp"

uint32_t now = 0;
uint32_t lastUpdate = 0;

Q4 Madgwick::q = {
	.w = 1.0,
	.x = 0.0,
	.y = 0.0,
	.z = 0.0
};

float invSqrt (float x)
{
	float halfx = 0.5f * x;
	float y = x;
	int32_t i = *(int32_t *)&y;
	i = 0x5f3759df - (i >> 1);
	y = *(float*)&i;
	y = y * (1.5f - (halfx * y * y));
	return y;
}

void madgwickFilter (double dt, double ax, double ay, double az, double gx, double gy, double gz)
{
    double recipNorm;
	double s0, s1, s2, s3;
	double qDot1, qDot2, qDot3, qDot4;
	double _2q0, _2q1, _2q2, _2q3, _4q0, _4q1, _4q2, _8q1, _8q2, q0q0, q1q1, q2q2, q3q3;

	// Convert gyroscope degrees/sec to radians/sec
	gx *= DEG_TO_RAD;
	gy *= DEG_TO_RAD;
	gz *= DEG_TO_RAD;

	// Rate of change of quaternion from gyroscope
	qDot1 = 0.5f * (-Madgwick::q.x * gx - Madgwick::q.y * gy - Madgwick::q.z * gz);
	qDot2 = 0.5f * (Madgwick::q.w * gx + Madgwick::q.y * gz - Madgwick::q.z * gy);
	qDot3 = 0.5f * (Madgwick::q.w * gy - Madgwick::q.x * gz + Madgwick::q.z * gx);
	qDot4 = 0.5f * (Madgwick::q.w * gz + Madgwick::q.x * gy - Madgwick::q.y * gx);

	// Compute feedback only if accelerometer measurement valid (avoids NaN in accelerometer normalisation)
	if (!((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f))) {
		// Normalise accelerometer measurement
		recipNorm = invSqrt(ax * ax + ay * ay + az * az);
		ax *= recipNorm;
		ay *= recipNorm;
		az *= recipNorm;

		// Auxiliary variables to avoid repeated arithmetic
		_2q0 = 2.0f * Madgwick::q.w;
		_2q1 = 2.0f * Madgwick::q.x;
		_2q2 = 2.0f * Madgwick::q.y;
		_2q3 = 2.0f * Madgwick::q.z;
		_4q0 = 4.0f * Madgwick::q.w;
		_4q1 = 4.0f * Madgwick::q.x;
		_4q2 = 4.0f * Madgwick::q.y;
		_8q1 = 8.0f * Madgwick::q.x;
		_8q2 = 8.0f * Madgwick::q.y;
		q0q0 = Madgwick::q.w * Madgwick::q.w;
		q1q1 = Madgwick::q.x * Madgwick::q.x;
		q2q2 = Madgwick::q.y * Madgwick::q.y;
		q3q3 = Madgwick::q.z * Madgwick::q.z;

		// Gradient decent algorithm corrective step
		s0 = _4q0 * q2q2 + _2q2 * ax + _4q0 * q1q1 - _2q1 * ay;
		s1 = _4q1 * q3q3 - _2q3 * ax + 4.0f * q0q0 * Madgwick::q.x - _2q0 * ay - _4q1 + _8q1 * q1q1 + _8q1 * q2q2 + _4q1 * az;
		s2 = 4.0f * q0q0 * Madgwick::q.y + _2q0 * ax + _4q2 * q3q3 - _2q3 * ay - _4q2 + _8q2 * q1q1 + _8q2 * q2q2 + _4q2 * az;
		s3 = 4.0f * q1q1 * Madgwick::q.z - _2q1 * ax + 4.0f * q2q2 * Madgwick::q.z - _2q2 * ay;
		recipNorm = invSqrt(s0 * s0 + s1 * s1 + s2 * s2 + s3 * s3); // normalise step magnitude

		s0 *= recipNorm;
		s1 *= recipNorm;
		s2 *= recipNorm;
		s3 *= recipNorm;

		// Apply feedback step
        qDot1 -= MADGWICK_BETA * s0;
        qDot2 -= MADGWICK_BETA * s1;
        qDot3 -= MADGWICK_BETA * s2;
        qDot4 -= MADGWICK_BETA * s3;
    }

	// Integrate rate of change of quaternion to yield quaternion
	Madgwick::q.w += qDot1 * dt;
	Madgwick::q.x += qDot2 * dt;
	Madgwick::q.y += qDot3 * dt;
	Madgwick::q.z += qDot4 * dt;

	// Normalise quaternion
	recipNorm = invSqrt(Madgwick::q.w * Madgwick::q.w + Madgwick::q.x * Madgwick::q.x + Madgwick::q.y * Madgwick::q.y + Madgwick::q.z * Madgwick::q.z);

	Madgwick::q.w *= recipNorm;
	Madgwick::q.x *= recipNorm;
	Madgwick::q.y *= recipNorm;
	Madgwick::q.z *= recipNorm;
}

void Madgwick::updateQuaternion (void)
{
    for (int i = 0; i < IT_COUNT; i++) { // iterate a fixed number of times per data read cycle
    	now = micros();

        double deltat = ((now - lastUpdate) / 1000000.0f); // set integration time by time elapsed since last nxp_filter update
        lastUpdate = now;

		madgwickFilter(deltat, IMU::acc.x, IMU::acc.y, IMU::acc.z, IMU::gyr.x, IMU::gyr.y, IMU::gyr.z);
    }
}
