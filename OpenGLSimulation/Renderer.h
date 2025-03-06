#pragma once

#include "Mesh.h"
#include "Camera.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void RenderMesh(Mesh& mesh, Camera& camera);
};

