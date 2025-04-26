#pragma once

struct Vector4f
{
	Vector4f(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
	Vector4f() { x = 0; y = 0; z = 0;  w = 0;}

	float x, y, z, w;

	bool operator==(const Vector4f& other) const
	{
		return (x == other.x) && (y == other.y) && (z == other.z) && (w == other.w);
	}
};
