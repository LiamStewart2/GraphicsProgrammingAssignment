#pragma once

#include "Mesh.h"

class Object
{
public:
	Object() {}
	~Object() {}

	Mesh* mesh = nullptr;
};