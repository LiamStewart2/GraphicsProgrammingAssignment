#pragma once

struct Color
{
	Color(float _r, float _g, float _b, float _a = 1.0f) : r(_r), g(_g), b(_b), a(_a) {}
	Color() : r(1), g(1), b(1), a(1) {}

	float r, g, b, a;
};