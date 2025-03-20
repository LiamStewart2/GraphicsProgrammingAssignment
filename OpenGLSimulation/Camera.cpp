#include "Camera.h"

void Camera::Update(double etime)
{
	handleMovement(etime);
	handleTurning();
}

void Camera::handleMovement(double etime)
{
	if (Keyboard::GetButtonState('w'))
	{
		eye.z -= 0.01f; 
		center.z -= 0.01f;
	}
	if (Keyboard::GetButtonState('s'))
	{
		eye.z += 0.01f; 
		center.z += 0.01f;
	}
	if(Keyboard::GetButtonState('a'))
	{
		eye.x = sin(etime * 0.001f) * 6;
		eye.z = cos(etime * 0.001f) * 6;
	}
	if (Keyboard::GetButtonState('d'))
	{
		eye.x += 0.01f;
		center.x += 0.01f;
	}
}

void Camera::handleTurning()
{
}
