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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
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
	monkeyObject = Object(&monkeyMesh, Transform({ 0, 0, -2.5 }, { 0.3f, 0.3f, 0.3f }, { -90, 0, 0 }));
}

void Application::MainLoop()
{
	//Callbacks
	glutKeyboardFunc(GLUTCallbacks::Keyboard);
	glutMouseFunc(GLUTCallbacks::HandleMouseButtonPressed);
	glutPassiveMotionFunc(GLUTCallbacks::HandleMouseMove);
	glutMotionFunc(GLUTCallbacks::HandleMouseMove);
	
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
	glutSwapBuffers();
}

void Application::Update()
{
	glutPostRedisplay();

	monkeyObject.transform.Position.y = sin(glutGet(GLUT_ELAPSED_TIME) * 0.005f) * 0.5;
	monkeyObject.transform.Rotation.y += 2;
}

void Application::HandleKeyboard(unsigned char key, int x, int y)
{
	if (key == 'a')
		monkeyObject.transform.Position.x -= 0.01;
	if (key == 'd')
		monkeyObject.transform.Position.x += 0.01;
}

void Application::HandleMouseButtonPressed(int button, int state, int x, int y)
{
	Mouse::SetMouseButtonState(button, state);
}

void Application::HandleMouseMove(int x, int y)
{
	Mouse::SetMousePosition(x, y);
}


