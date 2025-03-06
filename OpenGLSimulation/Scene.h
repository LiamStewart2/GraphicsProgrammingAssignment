#pragma once

#include "Renderer.h"
#include "Camera.h"
#include "Object.h"

class Scene
{
public:
	Scene();
	~Scene();

	void Render(Renderer* renderer);

private:
	Camera camera;
	std::vector<Object> objects;
};