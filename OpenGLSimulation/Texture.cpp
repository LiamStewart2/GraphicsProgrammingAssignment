#include "Texture.h"

// Bind Texture using an array of char's
void Texture::BindDataToTexture(const char* textureData)
{
	// generate a new OPENGL texture object
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	// push the data to the OPENGL texture object
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);

	// set the textures filtering methods
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// build the mipmaps for the textures
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, textureData);

	// un bind the texture
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::BindDataToTexture(const unsigned char* textureData)
{
	// generate a new OPENGL texture object
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	// push the data to the OPENGL texture object
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);

	// set the textures filtering methods
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// build the mipmaps for the textures
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, textureData);

	// un bind the texture
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