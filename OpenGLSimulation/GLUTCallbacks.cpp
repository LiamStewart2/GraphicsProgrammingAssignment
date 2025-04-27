#include "GLUTCallbacks.h"

#include "Application.h"

namespace GLUTCallbacks
{
	namespace
	{
		Application* app = nullptr;
	}

	void Init(Application *application)
	{
		app = application;
	}

	void Timer(int preferredRefresh)
	{
		int deltaTime = glutGet(GLUT_ELAPSED_TIME);

		app->Update();
		app->Display();

		deltaTime = glutGet(GLUT_ELAPSED_TIME) - deltaTime;

		glutTimerFunc(preferredRefresh - deltaTime, GLUTCallbacks::Timer, preferredRefresh);
	}

	void KeyboardDown(unsigned char key, int x, int y)
	{
		app->HandleKeyboardDown(key, x, y);
	}
	void KeyboardUp(unsigned char key, int x, int y)
	{
		app->HandleKeyboardUp(key, x, y);
	}

	void HandleMouseButtonPressed(int button, int state, int x, int y)
	{
		app->HandleMouseButtonPressed(button, state, x, y);
	}

	void HandleMouseMove(int x, int y)
	{
		app->HandleMouseMove(x, y);
	}
}