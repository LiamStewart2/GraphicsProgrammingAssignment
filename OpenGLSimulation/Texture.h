#pragma once

#include <Windows.h>

#include <GL/GL.h>
#include <GL/GLU.h>
#include "GL/freeglut.h"

struct Texture 
{
public:
	Texture() {}
	~Texture() {}

	void BindDataToTexture(const char* textureData);
	void BindDataToTexture(const unsigned char* textureData);

	void BindTexture();
	void UnbindTexture();

	GLuint textureID = -1;
	int width = 0; int height = 0;
};