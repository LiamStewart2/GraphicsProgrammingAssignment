#include "Camera.h"


void Camera::SetFocus(Object& object)
{
	center = object.transform.Position;
}

void Camera::Update()
{
	handleMovement();
}

void Camera::handleMovement()
{
	
}