#pragma once

#include <Windows.h>

#include <GL/GL.h>
#include <GL/GLU.h>
#include "GL/freeglut.h"

#include "GLUTCallbacks.h"

class Application
{
public:
	Application(int argc, char* argv[]);
	~Application();
	
	void Update();
private:

};

