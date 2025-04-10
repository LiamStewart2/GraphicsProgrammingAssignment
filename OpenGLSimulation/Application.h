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
#include "Texture.h"
#include "Light.h"
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
	void Init(int argc, char* argv[]);
	void LoadScene();
	void MainLoop();

	Scene scene;

	Mesh monkeyMesh;
	Mesh coolCubeMesh;
	Mesh plankMesh;

	std::vector<Object> objects;

	TextObject FPSText;
	TextObject ObjectNameText;

	Texture penguinTexture;
	Texture stoneTexture;
	Texture woodenPlankTexture;

	Material penguinMaterial;
	Material woodenPlankMaterial;

	Light light;

	Camera camera;
	unsigned int objectFocusIndex = 0;
	void SwitchObjectFocus();

	int lastFrameTime = 0;
	
};

