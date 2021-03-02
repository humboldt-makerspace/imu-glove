#ifndef ACTION_HPP
#define ACTION_HPP

#include "constants.h"

class Action {
private:
	/* variables */

	/* functions */

public:
	/* variables */
	static unsigned long actionTime;
	static Direction lastDirection;
	static Gesture currentGesture;

	/* functions */
	static void detectHandGesture (void);
	static Direction getDirection (void);
};

#endif
