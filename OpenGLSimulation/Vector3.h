#pragma once

#include <math.h>
#include <string>
#include <sstream>
#include <iomanip>

struct Vector3f
{
	Vector3f(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
	Vector3f() {x = 0; y = 0; z = 0;}

	float x, y, z;

	float Magnitude()
	{
		return (float) sqrt(x*x + y*y + z*z);
	}
	void Normalize()
	{
		float m = (float) sqrt(x*x + y*y + z*z);
		if(m <= 0.0001f) m = 1;
		x /= m;
		y /= m;
		z /= m;
	}
	Vector3f Normalized()
	{
		float m = (float)sqrt(x * x + y * y + z * z);
		if (m <= 0.0001f) m = 1;
		return Vector3f(x / m, y / m, z / m);
	}


	bool operator==(const Vector3f& other) const
	{
		return (x == other.x) && (y == other.y) && (z == other.z);
	}
	Vector3f operator+(const Vector3f& v) const
	{
		return Vector3f(x + v.x, y + v.y, z + v.z);
	}
	Vector3f operator-(const Vector3f& v) const
	{
		return Vector3f(x - v.x, y - v.y, z - v.z);
	}
	Vector3f operator*(const Vector3f& v) const
	{
		return Vector3f(x * v.x, y * v.y, z * v.z);
	}
	Vector3f operator/(const Vector3f& v) const
	{
		return Vector3f(x / v.x, y / v.y, z / v.z);
	}

	static float dot(Vector3f u, Vector3f v)
	{
		return (u.x * v.x + u.y * v.y + u.z * v.z);
	}
	static Vector3f Cross(Vector3f u, Vector3f v)
	{
		return Vector3f(
			u.y * v.z - u.z * v.y,
			-u.x * v.z + u.z * v.x,
			u.x * v.y - u.y * v.x
		);
	}

	std::string ToString()
	{
		// use a stream to set the decimal point precision
		std::ostringstream stream;
		stream << std::fixed << std::setprecision(2) << x << ", " << y << ", " << z;
		return stream.str();
	}
};

struct Vector3i
{
	Vector3i(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}
	Vector3i() { x = 0; y = 0; z = 0; }

	int x, y, z;
};