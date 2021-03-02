#include "utils/Orientation.hpp"
#include "system/Interface.hpp"

V3 Orientation::orientation;

V3 Orientation::updateOrientation (void)
{
	IMU::read(true);
	Madgwick::updateQuaternion();
	Orientation::orientation = VecUtils::computeDirectionFromQuaternion(Madgwick::q, VecUtils::upwardsDirection);
}

void Orientation::showOrientation (void)
{
	Serial.print("OR: x: ");
	Serial.print(Orientation::orientation.x);
	Serial.print(" y: ");
	Serial.print(Orientation::orientation.y);
	Serial.print(" z: ");
	Serial.println(Orientation::orientation.z);
}
