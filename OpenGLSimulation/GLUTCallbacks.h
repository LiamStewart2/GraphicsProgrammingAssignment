#pragma once

class Application;

namespace GLUTCallbacks
{
	void Init(Application* app);
	void Display();
	void Timer(int preferredRefresh);
	// x and y are mouse coordinates (window relative)
	void Keyboard(unsigned char key, int x, int y);
	void HandleMouseButtonPressed(int button, int state, int x, int y);
	void HandleMouseMove(int x, int y);

}