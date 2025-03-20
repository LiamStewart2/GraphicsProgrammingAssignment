#include "Application.h"

Application::Application(int argc, char* argv[])
{
	Init(argc, argv);
	LoadScene();
	camera = Camera({0, 0, 8}, {0, 0, 0}, {0, 1, 0});
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
	glFrontFace(GL_CCW);
}

void Application::LoadScene()
{
	FileLoader::LoadMeshFromOBJ("res/Mesh/monkey.obj", monkeyMesh);
	objects.push_back(Object(&monkeyMesh, Transform({ 2, 0, 0 }, { 0.3f, 0.3f, 0.3f }, { -90, 0, 0 })));
	objects.push_back(Object(&monkeyMesh, Transform({ -2, 0, 0 }, { 0.3f, 0.3f, 0.3f }, { -90, 0, 0 })));
}

void Application::MainLoop()
{
	//Callbacks
	glutKeyboardFunc(GLUTCallbacks::KeyboardDown);
	glutKeyboardUpFunc(GLUTCallbacks::KeyboardUp);
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

	for(Object object : objects)
		Renderer::RenderMesh(object, camera);

	glFlush();
	glutSwapBuffers();
}

void Application::Update()
{
	glutPostRedisplay();
	
	camera.Update();

	for(int i = 0; i < objects.size(); i++)
	{
		objects[i].transform.Position.y = sin(glutGet(GLUT_ELAPSED_TIME) * 0.004f);
		objects[i].transform.Rotation.y += 2;
	}

	camera.SetFocus(objects[objectFocusIndex]);
}

void Application::SwitchObjectFocus()
{
	objectFocusIndex += 1;
	if (objectFocusIndex >= objects.size())
		objectFocusIndex -= objects.size();
}

void Application::HandleKeyboardDown(unsigned char key, int x, int y)
{
	Keyboard::SetButtonPressedDown(key);
	SwitchObjectFocus();
}
void Application::HandleKeyboardUp(unsigned char key, int x, int y)
{
	Keyboard::SetButtonReleased(key);
}

void Application::HandleMouseButtonPressed(int button, int state, int x, int y)
{
	Mouse::SetMouseButtonState(button, state);
}
void Application::HandleMouseMove(int x, int y)
{
	Mouse::SetMousePosition(x, y);
}


