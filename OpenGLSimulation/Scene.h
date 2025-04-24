#pragma once

#include "TransformationManager.h"
#include "Camera.h"
#include "Object.h"
#include "SceneGraph.h"
#include "FileLoader.h"
#include "Input.h"
#include "Light.h"

class Scene
{
public:
	Scene();
	~Scene();

	void InitScene();

	SceneGraph* GetSceneGraph() { return &sceneGraph; }
	Camera* GetCamera() { return &camera; }
	Light* GetLight() { return& light; }
	Object* GetFocusObject() { return& objects[focusObjectIndex]; }

	void Update();
	void ToggleCameraObjectFocus();
	std::string ChangeFocusIndex();

	TransformationManager* getTransformationManager() { return &transformationManager; }

private:
	TransformationManager transformationManager;
	std::vector<Object> objects;
	SceneGraph sceneGraph;
	
	Light light;

	Camera camera;
	int focusObjectIndex;

	Mesh monkeyMesh;
	Texture stoneTexture;
	Material stoneMaterial;

};