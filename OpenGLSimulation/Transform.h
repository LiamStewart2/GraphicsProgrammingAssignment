#pragma once
#include "Vector3.h"

struct Transform
{
	Transform() {}
	Transform(Vector3f _position, Vector3f _scale, Vector3f _rotation) : Position(_position), Scale(_scale), Rotation(_rotation) {}

	Vector3f Position;
	Vector3f Scale;
	Vector3f Rotation;
};