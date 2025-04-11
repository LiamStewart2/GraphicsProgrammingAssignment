#pragma once

#include <Windows.h>

#include <iostream>

#include "Globals.h"
#include "Vector3.h"
#include "Input.h"
#include "Object.h"

class Camera
{
public:
	Camera(Vector3f _eye, Vector3f _center, Vector3f _up): eye(_eye), targetPosition(_eye), center(_center), up(_up) {  }
	Camera() { }
	~Camera() {}

	Vector3f eye, center, up;

	Vector3f movementSpeed = Vector3f(0.1f, 0.1f, 0.1f);
	Vector3f targetPosition;

	float mouseSensitivity = 0.5f;
	float mouseInterpolation = 0.3f;

	float distanceFromObjectFocus = 5;

	void Update();
	void TrackObject(Object* object);

	bool IsObjectTracking() { return (trackedObject != nullptr); }

	void RightMouseDown(int x, int y);
	void RightMouseUp(int x, int y);
private:
	void HandleObjectFocus();

	void HandleMovement();
	void FaceMouse();
	void SmoothTurning();
	
	Object* trackedObject = nullptr;

	Vector2i SavedMousePosition = Vector2i(0, 0);
	float dx = 0; float dy = 0;
	float tx = SCREEN_WIDTH / 2 - 120; float ty = SCREEN_HEIGHT / 2 + 15;
};

