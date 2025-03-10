#pragma once

#include <Windows.h>

#include <GL/GL.h>
#include <GL/GLU.h>
#include "GL/freeglut.h"

#include "GLUTCallbacks.h"
#include "FileLoader.h"
#include "Renderer.h"

class Application
{
public:
	Application(int argc, char* argv[]);
	~Application();
	
	void Update();
private:
	Mesh monkey; Camera camera;
	float rot = 0.0f;
};

