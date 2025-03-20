#pragma once

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
};

struct Vector3i
{
	Vector3i(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}
	Vector3i() { x = 0; y = 0; z = 0; }

	int x, y, z;
};