#pragma once

#include "Texture.h"
#include "Vector4.h"

class Material
{
public:
	Material() {}
	Material(Texture* _texture) : texture(_texture) {}
	Material(Texture* _texture, Vector4f _ambient, Vector4f _diffuse, Vector4f _specular, float _shininess) : texture(_texture), ambient(_ambient), diffuse(_diffuse), specular(_specular), shininess(_shininess) {}
	~Material() {}

	Texture* texture = nullptr;
	Vector4f ambient, diffuse, specular;
	float shininess;
};