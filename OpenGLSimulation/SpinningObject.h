#pragma once

#include "Object.h"

class SpinningObject : public Object
{
public:
	SpinningObject(Mesh* _mesh, Material* _material, Transform _transform, const char* _name = "object") : Object(_mesh, _material, _transform, _name) {}

	void Update() override 
	{
		transform.Rotation.x += 1;
		transform.Rotation.y += 1;
	}
};