#pragma once

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

	Vector2f GETTXTY() {return camera.GETTXTY(); }

	void InitScene();

	SceneGraph* GetSceneGraph() { return &sceneGraph; }
	Camera* GetCamera() { return &camera; }
	Light* GetLight() { return& light; }
	Object* GetFocusObject() { return& objects[focusObjectIndex]; }

	void Update();
	void ToggleCameraObjectFocus();
	std::string ChangeFocusIndex();

private:
	std::vector<Object> objects;
	SceneGraph sceneGraph;
	
	Light light;

	Camera camera;
	int focusObjectIndex;

	Mesh monkeyMesh;
	Texture stoneTexture;
	Material stoneMaterial;

};