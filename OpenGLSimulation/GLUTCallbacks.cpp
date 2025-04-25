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

	void Display()
	{
		if (app != nullptr)
		{
			app->Display();
		}
	}
	void Timer(int preferredRefresh)
	{
		glutTimerFunc(preferredRefresh, GLUTCallbacks::Timer, preferredRefresh);
		app->Update();
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