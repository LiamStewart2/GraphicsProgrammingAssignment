#pragma once

#include <Windows.h>

#include <GL/GL.h>
#include <GL/GLU.h>
#include "GL/freeglut.h"

#include "Mesh.h"
#include "Camera.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	static void RenderMesh(Mesh& mesh, Camera& camera, float rot);
};

