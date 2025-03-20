#pragma once

#include "Vector2.h"

enum MouseButton
{
	LEFT, MIDDLE, RIGHT
};

namespace Mouse
{
	void SetMouseButtonState(int button, int new_state);
	void SetMousePosition(int _x, int _y);
	Vector2i GetMousePosition();
	bool GetMouseButtonState(int button);
};

namespace Keyboard
{
	void SetButtonPressedDown(unsigned char key);
	void SetButtonReleased(unsigned char key);
	bool GetButtonState(unsigned char key);
};