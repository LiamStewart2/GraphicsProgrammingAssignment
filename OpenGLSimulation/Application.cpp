#include "Application.h"

Application::Application(int argc, char* argv[])
{
	FileLoader::LoadMeshFromOBJ("res/Mesh/monkey.obj", monkey);

	GLUTCallbacks::Init(this);

	//Window Initalization
	glutInit(&argc, argv);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("Simple OpenGL Program");

	//Callbacks
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(REFRESH_RATE_DELAY, GLUTCallbacks::Timer, REFRESH_RATE_DELAY);

	//Mainloop
	glutMainLoop();
}

Application::~Application()
{

}

void Application::Display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	Renderer::RenderMesh(monkey, camera, rot);

	glFlush();
}

void Application::Update()
{
	glutPostRedisplay();

	rot += 0.1f;
}