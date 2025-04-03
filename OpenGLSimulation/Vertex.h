#pragma once

#include "Vector2.h"
#include "Vector3.h"

struct Vertex
{
public:
	Vertex() : x(0), y(0), z(0), nx(0), ny(0), nz(0), tx(0), ty(0) {}
	Vertex(float _x, float _y, float _z, float _nx, float _ny, float _nz, float _tx, float _ty) : x(_x), y(_y), z(_z), nx(_nx), ny(_ny), nz(_nz), tx(_tx), ty(_ty) {}
	Vertex(Vector3f position, Vector3f normal, Vector2f textureCoordinate)
	{
		x = position.x; y = position.y; z = position.z;
		nx = normal.x; ny = normal.y; nz = normal.z;
		tx = textureCoordinate.x; ty = textureCoordinate.y;
	}
	~Vertex() {}

	float x, y, z;
	float nx, ny, nz;
	float tx, ty;
};