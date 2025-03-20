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

	void SetFocus(Object& object);
	void Update();
private:
	void handleMovement();
};

