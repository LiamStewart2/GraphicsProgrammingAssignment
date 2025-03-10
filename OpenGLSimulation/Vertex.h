#pragma once

struct Vertex
{
public:
	Vertex() : x(0), y(0), z(0) {}
	Vertex(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
	~Vertex() {}
	float x, y, z;
};