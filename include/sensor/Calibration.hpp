#ifndef CALIBRATION_HPP
#define CALIBRATION_HPP

#include "utils/VecUtils.hpp"

typedef struct calibrationData {
	V3 gyrOffset;
	double gyrThreshold;
	V3 accOffset;
	V3 accFactor;
} CalibData;

class Calibration {
private:
	/* variables */

	/* functions */

public:
	/* variables */
	static CalibData data;

	/* functions */
	static void performCalibration (void);
	static void showCalibrationData (void);
};

#endif
