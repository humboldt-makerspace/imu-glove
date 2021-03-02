#include "utils/Action.hpp"
#include "system/Interface.hpp"

unsigned long Action::actionTime = 0;
Direction Action::lastDirection = UNKNOWN_DIRECTION;
Gesture Action::currentGesture = UNKNOWN_GESTURE;

Direction Action::getDirection (void)
{
	double z = Orientation::orientation.z;
	double y = Orientation::orientation.y;
	if (z > 1.0 - DIRECTION_TOLERANCE) return UPWARDS;
	else if (z < DIRECTION_TOLERANCE && z > -DIRECTION_TOLERANCE) return HORIZONTAL;
	else if (z < -1.0 + DIRECTION_TOLERANCE) return DOWNWARDS;
	else return UNKNOWN_DIRECTION;
}

void Action::detectHandGesture (void)
{
	Direction newDirection = Action::getDirection();
	if (lastDirection != newDirection) {
		Action::actionTime = millis();
		lastDirection = newDirection;
	}
	if (newDirection == HORIZONTAL) {
		if (abs(IMU::acc.x) > 2.0) {
			Serial.println("X_SIDE");
			Action::currentGesture = X_SIDE;
			return;
		}
		else if (abs(IMU::acc.y) > 2.0) {
			Serial.println("Y_SIDE");
			Action::currentGesture = Y_SIDE;
			return;
		}
		else if (abs(IMU::acc.z) > 2.0) {
			Serial.println("Z_SIDE");
			Action::currentGesture = Z_SIDE;
			return;
		}
	}
	else if (newDirection == UPWARDS) {
		if (abs(IMU::acc.x) > 2.0) {
			Serial.println("X_UP");
			Action::currentGesture = X_UP;
			return;
		}
		else if (abs(IMU::acc.y) > 2.0) {
			Serial.println("Y_UP");
			Action::currentGesture = Y_UP;
			return;
		}
		else if (abs(IMU::acc.z) > 2.0) {
			Serial.println("Z_UP");
			Action::currentGesture = Z_UP;
			return;
		}
	}
	else if (newDirection == DOWNWARDS) {
		if (abs(IMU::acc.x) > 2.0) {
			Serial.println("X_DOWN");
			Action::currentGesture = X_DOWN;
			return;
		}
		else if (abs(IMU::acc.y) > 2.0) {
			Serial.println("Y_DOWN");
			Action::currentGesture = Y_DOWN;
			return;
		}
		else if (abs(IMU::acc.z) > 2.0) {
			Serial.println("Z_DOWN");
			Action::currentGesture = Z_DOWN;
			return;
		}
	} 
	/*
	if (millis() - Action::actionTime > HOLD_TIME) {
		Action::actionTime = millis();
		switch (newDirection) {
			case UPWARDS: {
				Serial.println("holding up");
				Action::currentGesture = UP_HOLD;
				break;
			}
			case DOWNWARDS: {
				Serial.println("holding down");
				Action::currentGesture = DOWN_HOLD;
				break;
			}
			default: {
				Action::currentGesture = UNKNOWN_GESTURE;
				break;
			}
		}
		return;
	}*/
	Action::currentGesture = UNKNOWN_GESTURE;
}
