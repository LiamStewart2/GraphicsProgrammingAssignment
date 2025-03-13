#pragma once

struct Vector2f
{
	Vector2f(float _x, float _y) : x(_x), y(_y) {}
	Vector2f() { x = 0; y = 0;}

	float x, y;
};

struct Vector2i
{
	Vector2i(int _x, int _y) : x(_x), y(_y){}
	Vector2i() { x = 0; y = 0;}

	int x, y;
};