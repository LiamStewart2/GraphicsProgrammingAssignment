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
			app->Update();
		}
	}
}