#include "utils/VecUtils.hpp"
#include "system/Interface.hpp"

const V3 VecUtils::upwardsDirection = {
	.x = 0.0,
	.y = 0.0,
	.z = 1.0
};

V3 scalarMultiply (double a, V3 in)
{
	V3 result;
	result.x = in.x * a;
	result.y = in.y * a;
	result.z = in.z * a;
	return result;
}

float dot (V3 a, V3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

V3 cross (V3 a, V3 b)
{
	V3 result;
	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return result;
}

V3 add (V3 a, V3 b)
{
	V3 result;
	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return result;
}

V3 reverse (V3 in)
{
	V3 result;
	result.x = -in.x;
	result.y = -in.y;
	result.z = -in.z;
	return result;
}

float distance (V3 a, V3 b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) +
				(a.y - b.y) * (a.y - b.y) +
				(a.z - b.z) * (a.z - b.z));
}

float vecMag (V3 in)
{
	return sqrt(in.x * in.x + in.y * in.y + in.z * in.z);
}

V3 normalizeVector (V3 in)
{
	if (in.x == 0.0 && in.y == 0.0 && in.z == 0.0) return in;
	float root = vecMag(in);
	V3 result;
	result.x = in.x / root;
	result.y = in.y / root;
	result.z = in.z / root;
	return result;
}

V3 VecUtils::computeDirectionFromQuaternion (Q4 in, V3 ref)
{
	V3 u;
	u.x = in.x;
	u.y = in.y;
	u.z = in.z;
	float s = 2 * in.w;
	V3 b = scalarMultiply(s, cross(u, ref));
	V3 d = ref;
	V3 f = scalarMultiply(2.0, cross(u, cross(u, ref)));
	return normalizeVector(add(add(b, d), f));
}









