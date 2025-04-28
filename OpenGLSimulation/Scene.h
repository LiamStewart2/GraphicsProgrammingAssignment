#pragma once

#include "TransformationManager.h"
#include "Camera.h"
#include "Object.h"
#include "SceneGraph.h"
#include "FileLoader.h"
#include "Input.h"
#include "Light.h"
#include "LinkedList.h"
#include "TextObject.h"

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
	std::vector<TextObject*>* GetTextObjectBuffer() {return &textObjects;}

	void Update();
	void ToggleCameraObjectFocus();
	void ChangeFocusIndex();

	void UpdateTransformationText();

	TransformationManager* getTransformationManager() { return &transformationManager; }

private:
	TransformationManager transformationManager;
	LinkedList<Object> objects;
	SceneGraph sceneGraph;

	std::vector<TextObject*> textObjects;
	std::vector<Material*> materials;

	Light light;

	Camera camera;
	int focusObjectIndex;

	int lastFrameTime = 0;
	void UpdateTransformTexts();

	void BuildHierarchy();
	void BuildBranchOfHierarchy(SceneGraphNode* node, int level, int& screenHeight);

	Mesh monkeyMesh;
	Mesh groundMesh;
	Mesh donutMesh;

	Texture stoneTexture;
	Material stoneMaterial;

	Texture grassTexture;
	Material grassMaterial;

	Texture penguinTexture;
	Material penguinMaterial;

	TextObject FPSText;
	TextObject instructionsText;

	TextObject ObjectNameText;
	TextObject TransformText;

	TextObject PositionText;
	TextObject ScaleText;
	TextObject RotationText;
};