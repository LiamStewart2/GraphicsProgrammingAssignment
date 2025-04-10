#pragma once

#include "Camera.h"
#include "Object.h"
#include "SceneGraph.h"
#include "FileLoader.h"
#include "Input.h"

class Scene
{
public:
	Scene();
	~Scene();

	void InitScene();

	SceneGraph* GetSceneGraph() { return &sceneGraph; }
	Camera* GetCamera() { return &camera; }

	void Update();
	std::string ChangeFocusIndex();

private:
	std::vector<Object> objects;
	SceneGraph sceneGraph;

	Camera camera;
	int focusObjectIndex;

	Mesh monkeyMesh;
	Texture stoneTexture;
	Material stoneMaterial;

};