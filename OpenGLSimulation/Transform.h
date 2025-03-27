#pragma once
#include "Vector3.h"
#include "Vector2.h"

struct Transform
{
	Transform() {}
	Transform(Vector3f _position, Vector3f _scale, Vector3f _rotation) : Position(_position), Scale(_scale), Rotation(_rotation) {}

	Vector3f Position;
	Vector3f Scale;
	Vector3f Rotation;
};

struct Transform2D
{
	Transform2D() {}
	Transform2D(Vector2f _position, Vector2f _scale, float _rotation) : Position(_position), Scale(_scale), Rotation(_rotation) {}

	Vector2f Position;
	Vector2f Scale;
	float Rotation = 0;
};