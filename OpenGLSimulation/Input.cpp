#include "Input.h"

#include <vector>

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

namespace Keyboard
{
	namespace
	{
		std::vector<unsigned char> keys;
	}

	void SetButtonPressedDown(unsigned char key)
	{
		if(keys.size() == 0)
		{
			keys.push_back(key);
			return;
		}

		for (unsigned char k : keys)
		{
			if(k == key)
				return;
		}

		keys.push_back(key);
	}

	void SetButtonReleased(unsigned char key)
	{
		for (int i = 0; i < keys.size(); i++)
		{
			if (keys[i] == key)
			{
				keys.erase(keys.begin() + i);
				return;
			}
		}
	}

	bool GetButtonState(unsigned char key)
	{
		for (unsigned char k : keys)
		{
			if (k == key)
				return true;
		}
		return false;
	}
}