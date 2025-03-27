#pragma once

#include "Transform.h"
#include "Sprite.h"

class Object2D
{
public:
	Object2D() {}
	Object2D(Sprite* _sprite, Transform2D _transform, const char* _name = "2D object") : sprite(_sprite), transform(_transform), name(_name) { }
	~Object2D() {}

	const char* name = nullptr;
	Transform2D transform;
	Sprite* sprite = nullptr;
};