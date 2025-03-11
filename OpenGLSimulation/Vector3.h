#pragma once

struct Vector3f
{
	Vector3f(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
	Vector3f() {x = 0; y = 0; z = 0;}

	float x, y, z;
};

struct Vector3i
{
	Vector3i(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}
	Vector3i() { x = 0; y = 0; z = 0; }

	int x, y, z;
};