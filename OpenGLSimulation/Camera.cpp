#include "Camera.h"


void Camera::SetFocus(const Object* object)
{
	target = object->transform.Position;
}

void Camera::Update(double etime)
{
	handleMovement(etime);
}

// The elapsed time
void Camera::handleMovement(double etime)
{
	center = center + (target - center) * smooth;
	etime = 2500;
	Vector3f targetPosition = target + Vector3f(cos(etime * rotationSpeed) * rotationRadius, yOffset, sin(etime * rotationSpeed) * rotationRadius);
	eye = eye + (targetPosition - eye) * smooth;
}