#ifndef VEC_UTILS_HPP
#define VEC_UTILS_HPP

typedef struct vector3d {
	double x;
	double y;
	double z;
} V3;

typedef struct quaternion {
	double w;
	double x;
	double y;
	double z;
} Q4;

class VecUtils {
private:
	/* variables */

	/* functions */

public:
	/* variables */
	static const V3 upwardsDirection;

	/* functions */
	static V3 computeDirectionFromQuaternion (Q4 in, V3 ref);
};

#endif
