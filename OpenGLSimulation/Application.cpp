#include "Application.h"

Application::Application(int argc, char* argv[])
{
	Init(argc, argv);
	LoadScene();
	MainLoop();
}

Application::~Application()
{

}

void Application::Init(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);

	//Window Initalization
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("Simple OpenGL Program");

	//GL Settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);
}

void Application::LoadScene()
{
	FileLoader::LoadMeshFromOBJ("res/Mesh/monkey.obj", monkeyMesh);
	monkeyObject = Object(&monkeyMesh, Transform({ 0, 0, -5 }, { 0.3f, 0.3f, 0.3f }, { 0, 0, 0 }));
}

void Application::MainLoop()
{
	//Callbacks
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(REFRESH_RATE_DELAY, GLUTCallbacks::Timer, REFRESH_RATE_DELAY);

	//Mainloop
	glutMainLoop();
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
