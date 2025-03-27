#pragma once

#include <Windows.h>
#include <string>

#include <GL/GL.h>
#include <GL/GLU.h>
#include "GL/freeglut.h"

#include "Input.h"
#include "Globals.h"
#include "GLUTCallbacks.h"
#include "FileLoader.h"
#include "Renderer.h"
#include "TextObject.h"
#include "Object2D.h";

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
	void Init(int argc, char* argv[]);
	void LoadScene();
	void MainLoop();

	Mesh monkeyMesh;
	std::vector<Object> objects;
	Object2D testImage;
	TextObject FPSText;
	TextObject ObjectNameText;
	
	Camera camera;
	unsigned int objectFocusIndex = 0;
	void SwitchObjectFocus();

	int lastFrameTime = 0;
	
};

