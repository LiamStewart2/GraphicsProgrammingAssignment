#pragma once

#include "Vector3.h"
#include "Input.h"
#include "Object.h"

class Camera
{
public:
	Camera(Vector3f _eye, Vector3f _center, Vector3f _up): eye(_eye), center(_center), up(_up) {}
	Camera() {}
	~Camera() {}

	Vector3f eye, center, up;
	Vector3f target;

	float rotationSpeed = 0.0005f;
	float rotationRadius = 3;
	float yOffset = 0.5f;
	Vector3f smooth = Vector3f(0.1f, 0.1f, 0.1f);

	void SetFocus(Object& object);
	void Update(double etime);
private:
	// The elapsed time
	void handleMovement(double etime);
};

