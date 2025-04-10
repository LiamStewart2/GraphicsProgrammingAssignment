#include "Camera.h"


void Camera::Update()
{
	if (Mouse::GetMouseButtonState(MouseButton::RIGHT) == false)
		FaceMouse();
	else
		SavedMousePosition = Mouse::GetMousePosition();
	SmoothTurning();

	HandleMovement();
}

// The elapsed time
void Camera::HandleMovement()
{
	if (Keyboard::GetButtonState('a'))
		targetPosition = targetPosition - (Vector3f::Cross(center - eye, up)) * movementSpeed;

	if (Keyboard::GetButtonState('d'))
		targetPosition = targetPosition + (Vector3f::Cross(center - eye, up)) * movementSpeed;

	eye = (eye - targetPosition) * Vector3f(0.1f, 0.1f, 0.1f);

}

void Camera::FaceMouse()
{
	tx -= (SavedMousePosition.x - Mouse::GetMousePosition().x) * mouseSensitivity;
	ty += (SavedMousePosition.y - Mouse::GetMousePosition().y) * mouseSensitivity;

	glutWarpPointer(SavedMousePosition.x, SavedMousePosition.y);
}

void Camera::SmoothTurning()
{
	dx += (tx - dx) * mouseInterpolation;
	dy += (ty - dy) * mouseInterpolation;

	center.x = eye.x + cos(dx / 180);
	center.z = eye.z + sin(dx / 180);
	center.y = eye.y + tan(dy / 180);
}

void Camera::RightMouseDown(int x, int y)
{
	SavedMousePosition = Vector2i(x, y);
	glutSetCursor(GLUT_CURSOR_NONE);
}
void Camera::RightMouseUp(int x, int y)
{

	glutWarpPointer(SavedMousePosition.x, SavedMousePosition.y);
	glutSetCursor(GLUT_CURSOR_LEFT_ARROW);

}