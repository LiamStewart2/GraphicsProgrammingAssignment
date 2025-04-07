#pragma once

#include "Texture.h"
#include "Vector4.h"

class Material
{
public:
	Material() {}
	Material(Texture* _texture) : texture(_texture) {}
	Material(Texture* _texture, Vector4f _ambient, Vector4f _diffuse, Vector4f _specular, float _shininess) : texture(_texture), shininess(_shininess) 
	{
		ambient[0] = _ambient.x; ambient[1] = _ambient.y; ambient[2] = _ambient.z; ambient[3] = _ambient.w; 
		diffuse[0] = _diffuse.x; diffuse[1] = _diffuse.y; diffuse[2] = _diffuse.z; diffuse[3] = _diffuse.w;
		specular[0] = _specular.x; specular[1] = _specular.y; specular[2] = _specular.z; specular[3] = _specular.w;
	}
	~Material() {}

	Texture* texture = nullptr;
	float ambient[4], diffuse[4], specular[4];
	float shininess;
};