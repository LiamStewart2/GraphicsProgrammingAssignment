#pragma once


#include <Windows.h>

#include <math.h>

#include "Object.h"

class BouncingObject : public Object
{
public:
	BouncingObject(Mesh* _mesh, Material* _material, Transform _transform, const char* _name = "object") : Object(_mesh, _material, _transform, _name) {}

	void Update() override
	{
		transform.Position.y = sin(glutGet(GLUT_ELAPSED_TIME) * 0.0005);
	}
};