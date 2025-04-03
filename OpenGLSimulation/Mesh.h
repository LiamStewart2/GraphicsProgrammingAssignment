#pragma once

#include <vector>

#include "Vertex.h"
#include "Vector2.h"
#include "Vector3.h"

class Mesh
{
public:
	Mesh() {}
	~Mesh() {}

	std::vector<Vertex> vertexBuffer;
};