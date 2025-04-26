#include "Scene.h"

Scene::Scene()
{
	camera = Camera({ 0, 0, 8 }, { 0, 0, 0 }, { 0, 1, 0 });
}

Scene::~Scene()
{
	for(int i = 0; i < textObjects.size(); i++)
		delete textObjects[i];
}

void Scene::InitScene()
{
	light = { {1, 1, 1, 0}, {0.3f, 0.3f, 0.3f, 1}, {0.7f, 0.7f, 0.7f, 1}, {0.5f, 0.5f, 0.5f, 1} };

	FileLoader::LoadMeshFromOBJ("res/Mesh/monkey.obj", monkeyMesh);

	FileLoader::LoadTextureFromBMP("res/Texture/stone.bmp", stoneTexture);

	stoneMaterial = Material(&stoneTexture, { 1, 1, 1, 1 }, { 1, 1, 1, 1 }, { 1, 1, 1, 1 }, 64);

	Object monkeyObject = Object(&monkeyMesh, &stoneMaterial, Transform({0, 0, 0}, {0.3f, 0.3f, 0.3f}, {0, 0, 0}), "Big monkey");
	Object monkeyObject2 = Object(&monkeyMesh, &stoneMaterial, Transform({2, 0, 0}, {0.3f, 0.3f, 0.3f}, {0, 0, 0}), "Right monkey");
	Object monkeyObject3 = Object(&monkeyMesh, &stoneMaterial, Transform({-2, 0, 0}, {0.3f, 0.3f, 0.3f}, {0, 0, 0}), "Left monkey");
	Object monkeyObject4 = Object(&monkeyMesh, &stoneMaterial, Transform({0, 2, 0}, {0.3f, 0.3f, 0.3f}, {0, 0, 0}), "small left monkey : )");
	Object monkeyObject5 = Object(&monkeyMesh, &stoneMaterial, Transform({ 0, 2, 0 }, { 0.3f, 0.3f, 0.3f }, { 0, 0, 0 }), "small right monkey");
	Object monkeyObject6 = Object(&monkeyMesh, &stoneMaterial, Transform({ 0, -3, 0 }, { 1, 1, 1 }, { 0, 0, 0 }), "same size left monkey");

	FPSText = TextObject(10, 10, GLUT_BITMAP_9_BY_15, "0", Vector3f(0, 1, 0));
	instructionsText = TextObject(SCREEN_WIDTH - 250, 10, GLUT_BITMAP_9_BY_15, "Controls on the README.md", Vector3f(0, 1, 0));

	ObjectNameText = TextObject(SCREEN_WIDTH - 250, SCREEN_HEIGHT - 15, GLUT_BITMAP_9_BY_15, "", Vector3f(0, 1, 0));
	TransformText = TextObject(SCREEN_WIDTH - 250, SCREEN_HEIGHT - 30, GLUT_BITMAP_9_BY_15, "Translate - X", Vector3f(0, 1, 0));

	PositionText = TextObject(SCREEN_WIDTH - 250, SCREEN_HEIGHT - 45, GLUT_BITMAP_9_BY_15, "Position x, y, z", Vector3f(0, 1, 0));
	ScaleText = TextObject(SCREEN_WIDTH - 250, SCREEN_HEIGHT - 60, GLUT_BITMAP_9_BY_15, "Scale x, y, z", Vector3f(0, 1, 0));
	RotationText = TextObject(SCREEN_WIDTH - 250, SCREEN_HEIGHT - 75, GLUT_BITMAP_9_BY_15, "Rotation x, y, z", Vector3f(0, 1, 0));


	objects.Push(monkeyObject);
	objects.Push(monkeyObject2);
	objects.Push(monkeyObject3);
	objects.Push(monkeyObject4);
	objects.Push(monkeyObject5);
	objects.Push(monkeyObject6);

	sceneGraph.InsertRootNode(new SceneGraphNode(&objects[0]));
	SceneGraphNode* node2 = sceneGraph.InsertNode(sceneGraph.GetRootNode(), new SceneGraphNode(&objects[1]));
	SceneGraphNode* node = sceneGraph.InsertNode(sceneGraph.GetRootNode(), new SceneGraphNode(&objects[2]));
	sceneGraph.InsertNode(node, new SceneGraphNode(&objects[3]));
	sceneGraph.InsertNode(node2, new SceneGraphNode(&objects[4]));
	sceneGraph.InsertNode(node, new SceneGraphNode(&objects[5]));

	textObjects = {&FPSText, &ObjectNameText, &TransformText, &PositionText, &ScaleText, &RotationText, &instructionsText};

	ObjectNameText.text = objects[focusObjectIndex].name;
	UpdateTransformationText();

	BuildHierarchy();
}

void Scene::Update()
{
	transformationManager.Update(&objects[focusObjectIndex]);

	objects[1].transform.Rotation.y = sin(glutGet(GLUT_ELAPSED_TIME) * 0.001) * 180;

	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	int deltaTime = currentTime - lastFrameTime;
	lastFrameTime = currentTime;

	if (deltaTime > 0)
		FPSText.text = std::to_string(1000 / deltaTime);

	lastFrameTime = glutGet(GLUT_ELAPSED_TIME);
	UpdateTransformTexts();

	camera.Update();

	sceneGraph.UpdateObjectWorldPositions();

}

void Scene::UpdateTransformationText()
{
	std::string transformMode = transformationManager.getTransformModeText();
	std::string transformAxis = transformationManager.getTransformAxisText();

	TransformText.text = transformMode + " - " + transformAxis;
}

void Scene::UpdateTransformTexts()
{
	PositionText.text = "Position: " + objects[focusObjectIndex].transform.Position.ToString();
	ScaleText.text = "Scale:    " + objects[focusObjectIndex].transform.Scale.ToString();
	RotationText.text = "Rotation: " + objects[focusObjectIndex].transform.Rotation.ToString();
}

// Recursivly iterate through the tree and create the Hierarchy text objects
void Scene::BuildHierarchy()
{
	int level = 0; int screenHeight = 20;
	BuildBranchOfHierarchy(sceneGraph.GetRootNode(), level, screenHeight);
}

void Scene::BuildBranchOfHierarchy(SceneGraphNode* node, int level, int& screenHeight)
{
	TextObject* textBranch = new TextObject((float)(level * 15 + 15), (float)(SCREEN_HEIGHT - screenHeight), GLUT_BITMAP_9_BY_15, node->GetNodeObject()->name, Vector3f(0, 1, 0));
	textObjects.push_back(textBranch);

	if (node->GetNumberOfChildNodes() > 0)
	{
		for (int i = 0; i < node->GetNumberOfChildNodes(); i++)
		{
			screenHeight += 15;
			BuildBranchOfHierarchy(node->GetChildNode(i), level + 1, screenHeight);
		}
	}
}

void Scene::ToggleCameraObjectFocus()
{
	if(camera.IsObjectTracking() == false)
		camera.TrackObject(&objects[focusObjectIndex]);
	else
		camera.TrackObject(nullptr);
}

void Scene::ChangeFocusIndex()
{
	focusObjectIndex += 1;
	if (focusObjectIndex >= objects.Size())
		focusObjectIndex -= objects.Size();

	if(camera.IsObjectTracking())
		camera.TrackObject(&objects[focusObjectIndex]);

	ObjectNameText.text = objects[focusObjectIndex].name;
}