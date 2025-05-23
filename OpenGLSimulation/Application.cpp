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

// Disable VSync, Windows specific
void Application::DisableVSync() {
	typedef BOOL(WINAPI* PFNWGLSWAPINTERVALEXTPROC)(int);
	PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT =
		(PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");

	if (wglSwapIntervalEXT)
		wglSwapIntervalEXT(0);  // 0 = VSync off
}

void Application::Init(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);

	//Window Initalization
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("Simple OpenGL Program");
	DisableVSync();

//full screen toggle in Globals.h
#ifdef FULLSCREEN
	glutFullScreen();
#endif

	//GL Settings
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_NORMALIZE);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor3f(1.0f, 1.0f, 1.0f);
	glClearColor(0.2f, 0.5f, 1.0f, 1);
}

void Application::LoadScene()
{
	scene.InitScene();
}

void Application::MainLoop()
{
	//Callbacks
	glutKeyboardFunc(GLUTCallbacks::KeyboardDown);
	glutKeyboardUpFunc(GLUTCallbacks::KeyboardUp);

	glutMouseFunc(GLUTCallbacks::HandleMouseButtonPressed);
	glutPassiveMotionFunc(GLUTCallbacks::HandleMouseMove);
	glutMotionFunc(GLUTCallbacks::HandleMouseMove);

	glutTimerFunc(REFRESH_RATE_DELAY, GLUTCallbacks::Timer, REFRESH_RATE_DELAY);

	//Mainloop

	glutMainLoop();
}

void Application::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	renderer.RenderScene(scene);

	glFlush();
	glutSwapBuffers();
}

void Application::Update()
{
	glutPostRedisplay();

	scene.Update();
}

void Application::HandleKeyboardDown(unsigned char key, int x, int y)
{
	char lowercaseKey = static_cast<char>(std::tolower(key));

	Keyboard::SetButtonPressedDown(lowercaseKey);
	if(lowercaseKey == ' ')
		scene.ChangeFocusIndex();
	else if(lowercaseKey == 'e')
		scene.ToggleCameraObjectFocus();

	else if(lowercaseKey == 'z')
		scene.getTransformationManager()->RotateTransformAxis(-1);
	else if(lowercaseKey == 'x')
		scene.getTransformationManager()->RotateTransformAxis(1);

	else if (lowercaseKey == 'q')
		glutLeaveMainLoop();
	
	scene.getTransformationManager()->SetTransformMode(lowercaseKey);
	scene.UpdateTransformationText();
}
void Application::HandleKeyboardUp(unsigned char key, int x, int y)
{
	char lowercaseKey = static_cast<char>(std::tolower(key));
	Keyboard::SetButtonReleased(lowercaseKey);
}

void Application::HandleMouseButtonPressed(int button, int state, int x, int y)
{
	Mouse::SetMouseButtonState(button, state);
	
	if (button == MouseButton::RIGHT)
	{
		if (state == 0)
			scene.GetCamera()->RightMouseDown(x, y);
		else if(state == 1)
			scene.GetCamera()->RightMouseUp(x, y);
	}
}
void Application::HandleMouseMove(int x, int y)
{
	Mouse::SetMousePosition(x, y);
}