#ifndef ORIENTATION_HPP
#define ORIENTATION_HPP

#include "utils/VecUtils.hpp"

class Orientation {
private:
	/* variables */

	/* functions */

public:
	/* variables */
	static V3 orientation;

	/* functions */
	static V3 updateOrientation (void);
	static void showOrientation (void);
};

#endif
