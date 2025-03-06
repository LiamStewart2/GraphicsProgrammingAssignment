#pragma once

#include "glm/glm.hpp"

struct Vertex
{
public:
	Vertex(glm::vec3 pos, glm::vec3 col, glm::vec2 textureCord) : position(pos), colour(col), textureCoordinate(textureCord) {}
	~Vertex() {}

	glm::vec3 position = glm::vec3(0);
	glm::vec3 colour = glm::vec3(0);
	glm::vec2 textureCoordinate = glm::vec2(0);
};