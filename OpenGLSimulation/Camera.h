#pragma once

#include "Vector3.h"
#include "Input.h"

class Camera
{
public:
	Camera(Vector3f _eye, Vector3f _center, Vector3f _up): eye(_eye), center(_center), up(_up) {}
	Camera() {}
	~Camera() {}

	Vector3f eye, center, up;

	void Update(double etime);
private:
	void handleMovement(double etime);
	void handleTurning();
};

