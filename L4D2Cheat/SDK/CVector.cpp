#include "CVector.h"

ÑVector::ÑVector(float X, float Y, float Z)
{
	x = X; y = Y; z = Z;
}

ÑVector::ÑVector(void)
{
	x = y = z = 0;
#ifdef _DEBUG
#ifdef VECTOR_PARANOIA
	// Initialize to NAN to catch errors
	x = y = z = VEC_T_NAN;
#endif
#endif
}

ÑVector ÑVector::operator*(float fl) const
{
	ÑVector res;
	res.x = x * fl;
	res.y = y * fl;
	res.z = z * fl;
	return res;
}

ÑVector ÑVector::operator*(const ÑVector& v) const
{
	ÑVector res;
	res.x = x * v.x;
	res.y = y * v.y;
	res.z = z * v.z;
	return res;
}

ÑVector ÑVector::operator+(const ÑVector& v) const
{
	ÑVector res;
	res.x = x + v.x;
	res.y = y + v.y;
	res.z = z + v.z;
	return res;
}