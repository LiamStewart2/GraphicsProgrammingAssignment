#include "Mouse.h"

namespace Mouse
{
	namespace
	{
		int mouse_x; int mouse_y;
		bool mouse_buttons[3] = { 0, 0, 0 };
	}

	void SetMouseButtonState(int button, int new_state)
	{

		if (button >= 3)
			return;
		mouse_buttons[button] = new_state;
	}

	void SetMousePosition(int _x, int _y) 
	{ 
		mouse_x = _x; 
		mouse_y = _y; 
	}

	Vector2i GetMousePosition() 
	{ 
		return Vector2i(mouse_x, mouse_y); 
	}

	bool GetMouseButtonState(int button)
	{
		if (button >= 3)
			return false;
		else
			return mouse_buttons[button];
	}

}