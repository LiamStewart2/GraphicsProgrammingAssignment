#pragma once

#include "Transform.h"
#include "Mesh.h"

class Object
{
public:
	Object() {}
	Object(Mesh* _mesh, Transform _transform, const char* _name = "object") : mesh(_mesh), transform(_transform), name(_name) {}
	~Object() {}

	const char* name = nullptr;
	Transform transform;
	Mesh* mesh = nullptr;
};