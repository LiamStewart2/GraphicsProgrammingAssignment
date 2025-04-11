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
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("Simple OpenGL Program");

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

	// Set Light Data
	Renderer::SetLight(&light);
}

void Application::LoadScene()
{
	scene.InitScene();

	FPSText = TextObject(10, SCREEN_HEIGHT - 25, GLUT_BITMAP_9_BY_15, "0", Vector3f(0, 1, 0));
	ObjectNameText = TextObject(10, 10, GLUT_BITMAP_9_BY_15, "", Vector3f(0, 1, 0));
	DebugText = TextObject(10, 30, GLUT_BITMAP_9_BY_15, "x, y", Vector3f(0, 1, 0));

	light = { {1, 1, 1, 0}, {0.3, 0.3, 0.3, 1}, {0.7, 0.7, 0.7, 1}, {0.5, 0.5, 0.5, 1} };

	//testImage = Object2D(nullptr, Transform2D({ 500, 500 }, { 100, 100 },45), Color(0, 0, 1, 0.5f));
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

	Renderer::RenderScene(scene);

	Renderer::ResetMaterial();

	Renderer::RenderTextObject(FPSText);
	Renderer::RenderTextObject(ObjectNameText);
	//Renderer::RenderTextObject(DebugText);


	glFlush();
	glutSwapBuffers();
}

void Application::Update()
{
	glutPostRedisplay();
	
	FPSText.text = std::to_string((int)floor(1000 / (glutGet(GLUT_ELAPSED_TIME) - lastFrameTime)));
	lastFrameTime = glutGet(GLUT_ELAPSED_TIME);

	scene.Update();
}

void Application::SwitchObjectFocus()
{
	ObjectNameText.text = scene.ChangeFocusIndex();
}

void Application::HandleKeyboardDown(unsigned char key, int x, int y)
{
	Keyboard::SetButtonPressedDown(key);
	if(key == ' ')
		SwitchObjectFocus();
	else if(key == 'e')
		scene.ToggleCameraObjectFocus();
}
void Application::HandleKeyboardUp(unsigned char key, int x, int y)
{
	Keyboard::SetButtonReleased(key);
}

void Application::HandleMouseButtonPressed(int button, int state, int x, int y)
{
	Mouse::SetMouseButtonState(button, state);

	if (button == MouseButton::RIGHT)
	{
		if (state == 0)
			camera.RightMouseDown(x, y);
		else if(state == 1)
			camera.RightMouseUp(x, y);
	}
}
void Application::HandleMouseMove(int x, int y)
{
	Mouse::SetMousePosition(x, y);
}