#include "Camera.h"

void Camera::Update(double etime)
{
	handleMovement(etime);
	handleTurning();
}

void Camera::handleMovement(double etime)
{
	eye.x = sin(etime * 0.001f) * 6;
	eye.z = cos(etime * 0.001f) * 6;
}

void Camera::handleTurning()
{
}
