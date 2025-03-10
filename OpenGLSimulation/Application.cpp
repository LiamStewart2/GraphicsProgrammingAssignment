#include "Application.h"
#include <iostream>

Application::Application(int argc, char* argv[])
{
	FileLoader::LoadMeshFromOBJ("res/Mesh/monkey.obj", monkey);

	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("Simple OpenGL Program");
	glutDisplayFunc(GLUTCallbacks::Display);
	glutIdleFunc(GLUTCallbacks::Update);
	glutMainLoop();
}

Application::~Application()
{

}

void Application::Update()
{
	glClear(GL_COLOR_BUFFER_BIT);

	rot += 0.01f;
	Renderer::RenderMesh(monkey, camera, rot);

	glFlush();
}