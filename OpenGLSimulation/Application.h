#pragma once

#include <Windows.h>

#include <GL/GL.h>
#include <GL/GLU.h>
#include "GL/freeglut.h"

#include "Mouse.h"
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
	
	void HandleKeyboard(unsigned char key, int x, int y);
	void HandleMouseButtonPressed(int button, int state, int x, int y);
	void HandleMouseMove(int x, int y);

private:
	void Init(int argc, char* argv[]);
	void LoadScene();
	void MainLoop();

	Mesh monkeyMesh; 
	Object monkeyObject;
	
	Camera camera;
	float rot = 0.0f;
};

