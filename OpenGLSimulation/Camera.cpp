#include "Camera.h"


void Camera::SetFocus(Object& object)
{
	target = object.transform.Position;
}

void Camera::Update()
{
	handleMovement();
}

void Camera::handleMovement()
{
	center = center + (target - center) * Vector3f( 0.1f, 0.1f, 0.1f);
}