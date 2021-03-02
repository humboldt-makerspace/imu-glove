#ifndef IMU_HPP
#define IMU_HPP

#include "utils/VecUtils.hpp"

class IMU {
private:
	/* variables */

	/* functions */

public:
	/* variables */
	static V3 acc;
	static V3 gyr;
	static unsigned long sleepTimer;

	/* functions */
	static void init (void);
	static void read (bool calibrated);
	static void showData (void);
};

#endif
