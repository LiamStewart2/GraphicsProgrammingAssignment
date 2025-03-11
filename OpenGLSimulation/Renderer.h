#pragma once

#include <Windows.h>

#include <GL/GL.h>
#include <GL/GLU.h>
#include "GL/freeglut.h"

#include "Object.h"
#include "Camera.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	static void RenderMesh(Object& object, Camera& camera);
};

