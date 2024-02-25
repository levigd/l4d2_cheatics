#include "CVector.h"

�Vector::�Vector(float X, float Y, float Z)
{
	x = X; y = Y; z = Z;
}

�Vector::�Vector(void)
{
	x = y = z = 0;
#ifdef _DEBUG
#ifdef VECTOR_PARANOIA
	// Initialize to NAN to catch errors
	x = y = z = VEC_T_NAN;
#endif
#endif
}

�Vector �Vector::operator*(float fl) const
{
	�Vector res;
	res.x = x * fl;
	res.y = y * fl;
	res.z = z * fl;
	return res;
}

�Vector �Vector::operator*(const �Vector& v) const
{
	�Vector res;
	res.x = x * v.x;
	res.y = y * v.y;
	res.z = z * v.z;
	return res;
}

�Vector �Vector::operator+(const �Vector& v) const
{
	�Vector res;
	res.x = x + v.x;
	res.y = y + v.y;
	res.z = z + v.z;
	return res;
}