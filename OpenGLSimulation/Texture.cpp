#include "Texture.h"

void Texture::BindDataToTexture(const char* textureData)
{
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::BindTexture()
{
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::UnbindTexture()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}