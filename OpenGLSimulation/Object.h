#pragma once

#include "Transform.h"
#include "Mesh.h"
#include "Material.h"

class Object
{
public:
	Object() {}
	Object(Mesh* _mesh, Material* _material, Transform _transform, const char* _name = "object") : mesh(_mesh), material(_material), transform(_transform), name(_name) {}
	~Object() {}

	virtual void Update() {}

	const char* name = nullptr;
	Transform transform;
	Transform worldTransform;
	Mesh* mesh = nullptr;
	Material* material = nullptr;
};