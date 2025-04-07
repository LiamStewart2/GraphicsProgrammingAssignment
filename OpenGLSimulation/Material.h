#pragma once

#include "Texture.h"

class Material
{
public:
	Material() {}
	Material(Texture* _texture) : texture(_texture) {}
	~Material() {}

	Texture* texture = nullptr;
};