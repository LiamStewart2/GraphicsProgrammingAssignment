#pragma once

#include "Vector3.h"

struct Ray {
	Vector3f rayOrigin = Vector3f(0, 0, 0);
	Vector3f rayDirection = Vector3f(0, 0, 0);
};