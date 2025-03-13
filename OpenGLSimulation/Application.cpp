#include "Application.h"

Application::Application(int argc, char* argv[])
{
	FileLoader::LoadMeshFromOBJ("res/Mesh/monkey.obj", monkeyMesh);
	monkeyObject = Object(&monkeyMesh, Transform({0, 0, -5}, {0.3f, 0.3f, 0.3f}, {-90, 0, 0}));

	GLUTCallbacks::Init(this);

	//Window Initalization
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("Simple OpenGL Program");

	//GL Settings
	//TODO TEST THESE ARE ACTUALLY ON
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Renderer::RenderMesh(monkeyObject, camera);

	glFlush();
}

void Application::Update()
{
	glutPostRedisplay();

	monkeyObject.transform.Rotation.y += 1;

	if (monkeyObject.transform.Rotation.y >= 360)
		monkeyObject.transform.Rotation.y -= 360;
}