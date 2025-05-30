#pragma once

#include <Windows.h>
#include <string>
#include <iostream>

#include <GL/GL.h>
#include <GL/GLU.h>
#include "GL/freeglut.h"

#include "Input.h"
#include "Globals.h"
#include "GLUTCallbacks.h"
#include "Renderer.h"
#include "Scene.h"

class Application
{
public:
	Application(int argc, char* argv[]);
	~Application();
	
	void Display();
	void Update();
	
	void HandleKeyboardDown(unsigned char key, int x, int y);
	void HandleKeyboardUp(unsigned char key, int x, int y);
	void HandleMouseButtonPressed(int button, int state, int x, int y);
	void HandleMouseMove(int x, int y);

private:
	Renderer renderer;

	void Init(int argc, char* argv[]);
	void DisableVSync();

	void LoadScene();
	void MainLoop();

	Scene scene;
};

