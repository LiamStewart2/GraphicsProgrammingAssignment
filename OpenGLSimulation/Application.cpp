#include "Application.h"

Application::Application(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutCreateWindow("Simple OpenGL Program");
	glutInitWindowSize(800, 800);
	glutDisplayFunc(GLUTCallbacks::Display);
	glutMainLoop();
}

Application::~Application()
{
}

void Application::Update()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);

	glColor4f(1, 1, 0, 1);

	glVertex2f(-0.75, 0.5);
	glVertex2f(0.75, 0.5);
	glVertex2f(0.75, -0.5);
	glVertex2f(-0.75, -0.5);

	glEnd();
	glFlush();
}