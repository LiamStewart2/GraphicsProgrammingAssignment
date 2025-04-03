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

	std::vector<Vector3f> vertexPositions;
	std::vector<Vector3f> vertexNormals;
	std::vector<Vector2f> vertexTextureCoordinates;

	std::vector<Vector3i> faces;
};