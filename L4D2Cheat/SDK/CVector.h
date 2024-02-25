#pragma once

class �Vector
{
public:
	�Vector(float X, float Y, float Z);
	�Vector();
	inline �Vector operator*(float fl) const;
	inline �Vector operator*(const �Vector& v) const;

	inline �Vector operator+(const �Vector& v) const;

	float x, y, z;
	inline float& operator[](int i)
	{
		return ((float*)this)[i];
	}
	inline float operator[](int i) const
	{
		return ((float*)this)[i];
	}

	float LengthSqr(void) const
	{
		return (x * x + y * y + z * z);
	}

};

class CVector3
{
public:
	float x, y, z;
};

class CVector2
{
public:
	float x, y;
};

