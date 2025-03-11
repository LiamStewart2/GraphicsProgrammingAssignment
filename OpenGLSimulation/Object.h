#pragma once

#include "Transform.h"
#include "Mesh.h"

class Object
{
public:
	Object() {}
	Object(Mesh* _mesh, Transform _transform) : mesh(_mesh), transform(_transform) {}
	~Object() {}

	Transform transform;
	Mesh* mesh = nullptr;
};