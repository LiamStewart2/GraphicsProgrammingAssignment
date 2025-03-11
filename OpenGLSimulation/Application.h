#pragma once

#include <Windows.h>

#include <GL/GL.h>
#include <GL/GLU.h>
#include "GL/freeglut.h"

#include "Globals.h"
#include "GLUTCallbacks.h"
#include "FileLoader.h"
#include "Renderer.h"

class Application
{
public:
	Application(int argc, char* argv[]);
	~Application();
	
	void Display();
	void Update();
private:
	Mesh monkeyMesh; 
	Object monkeyObject;
	
	Camera camera;
	float rot = 0.0f;
};

