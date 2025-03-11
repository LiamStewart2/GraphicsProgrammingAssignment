#pragma once

class Application;

namespace GLUTCallbacks
{
	void Init(Application* app);
	void Display();
	void Timer(int preferredRefresh);
}