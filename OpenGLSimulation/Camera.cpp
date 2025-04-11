#include "Camera.h"


void Camera::Update()
{
	if (trackedObject != nullptr)
	{
		HandleObjectFocus();
	}
	else
	{
		SmoothTurning();

	
		if (Mouse::GetMouseButtonState(MouseButton::RIGHT) == false)
			FaceMouse();
		else
			SavedMousePosition = Mouse::GetMousePosition();

		HandleMovement();
	}
}

void Camera::TrackObject(Object* object)
{
	trackedObject = object;
}

void Camera::HandleObjectFocus()
{
	int time = glutGet(GLUT_ELAPSED_TIME);

	center = trackedObject->worldPosition;

	targetPosition.x = center.x + (cos(time * 0.001) * distanceFromObjectFocus);
	targetPosition.z = center.z + (sin(time * 0.001) * distanceFromObjectFocus);

	eye = eye + (targetPosition - eye) * movementSpeed;
}

// uses the cross product to find the directions to move to
void Camera::HandleMovement()
{
	Vector3f forward = (center - eye).Normalized();
	Vector3f strafe = Vector3f::Cross(forward, up).Normalized();

	if (Keyboard::GetButtonState('a'))
		targetPosition = targetPosition - strafe * movementSpeed;
	if (Keyboard::GetButtonState('d'))
		targetPosition = targetPosition + strafe * movementSpeed;

	if(Keyboard::GetButtonState('w'))
		targetPosition = targetPosition + forward * movementSpeed;
	if (Keyboard::GetButtonState('s'))
		targetPosition = targetPosition - forward * movementSpeed;

	eye = eye + (targetPosition - eye) * movementSpeed;

}

// sets the target angles for the camera
void Camera::FaceMouse()
{
	tx -= (SavedMousePosition.x - Mouse::GetMousePosition().x) * mouseSensitivity;
	ty += (SavedMousePosition.y - Mouse::GetMousePosition().y) * mouseSensitivity;

	glutWarpPointer(SavedMousePosition.x, SavedMousePosition.y);
}

// Uses trigonometry to find the view direction of the camera
void Camera::SmoothTurning()
{
	dx += (tx - dx) * mouseInterpolation;
	dy += (ty - dy) * mouseInterpolation;

	center.x = eye.x + cos(dx / 180);
	center.z = eye.z + sin(dx / 180);
	center.y = eye.y + tan(dy / 180);
}

//Hides and Unhides the cursor
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