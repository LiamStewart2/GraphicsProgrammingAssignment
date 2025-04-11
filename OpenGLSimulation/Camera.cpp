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

	if (trackedObject != nullptr)
	{
		Vector3f direction = (eye - object->worldPosition).Normalized();
		angleFromObject = atan2(direction.z, direction.x);
	}
}

void Camera::HandleObjectFocus()
{
	angleFromObject += 0.01f;
	center = center + (trackedObject->worldPosition - center) * movementSpeed;

	targetPosition.x = center.x + (cos(angleFromObject) * distanceFromObjectFocus);
	targetPosition.z = center.z + (sin(angleFromObject) * distanceFromObjectFocus);

	eye = eye + (targetPosition - eye) * movementSpeed;

	FocusWorldPosition(center);
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
	int deltaMouseX = -(SavedMousePosition.x - Mouse::GetMousePosition().x);
	int deltaMouseY = (SavedMousePosition.y - Mouse::GetMousePosition().y);

	float deltaDegressX = deltaMouseX * 3.14 / 180;
	float deltaDegressY = deltaMouseY * 3.14 / 180;

	targetAngleX += deltaDegressX * mouseSensitivity;
	targetAngleY += deltaDegressY * mouseSensitivity;

	glutWarpPointer(SavedMousePosition.x, SavedMousePosition.y);
}

// Uses trigonometry to find the view direction of the camera
void Camera::SmoothTurning()
{
	angleX += (targetAngleX - angleX) * mouseInterpolation;
	angleY += (targetAngleY - angleY) * mouseInterpolation;

	center.x = eye.x + cos(angleX);
	center.z = eye.z + sin(angleX);
	center.y = eye.y + tan(angleY);

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

// set the target x and y to a position in the 3d space
void Camera::FocusWorldPosition(Vector3f position)
{
	Vector3f direction = (position - eye).Normalized();

	targetAngleX = atan2(direction.z, direction.x);
	targetAngleY = atan2(direction.y, sqrt(direction.x * direction.x + direction.z * direction.z));

	angleX = targetAngleX;
	angleY = targetAngleY;

	targetPosition = eye;
}