#include "Scene.h"

Scene::Scene()
{
	camera = Camera({ 0, 0, 8 }, { 0, 0, 0 }, { 0, 1, 0 });
}

Scene::~Scene()
{
}

void Scene::InitScene()
{
	light = { {1, 1, 1, 0}, {0.3, 0.3, 0.3, 1}, {0.7, 0.7, 0.7, 1}, {0.5, 0.5, 0.5, 1} };

	FileLoader::LoadMeshFromOBJ("res/Mesh/monkey.obj", monkeyMesh);

	FileLoader::LoadTextureFromBMP("res/Texture/stone.bmp", stoneTexture);

	stoneMaterial = Material(&stoneTexture, { 1, 1, 1, 1 }, { 1, 1, 1, 1 }, { 1, 1, 1, 1 }, 64);

	Object monkeyObject = Object(&monkeyMesh, &stoneMaterial, Transform({0, 0, 0}, {0.3f, 0.3f, 0.3f}, {0, 0, 0}), "Big monkey");
	Object monkeyObject2 = Object(&monkeyMesh, &stoneMaterial, Transform({2, 0, 0}, {0.3f, 0.3f, 0.3f}, {0, 0, 0}), "Right monkey");
	Object monkeyObject3 = Object(&monkeyMesh, &stoneMaterial, Transform({-2, 0, 0}, {0.3f, 0.3f, 0.3f}, {0, 0, 0}), "Left monkey");
	Object monkeyObject4 = Object(&monkeyMesh, &stoneMaterial, Transform({0, 2, 0}, {0.3f, 0.3f, 0.3f}, {0, 0, 0}), "small left monkey : )");
	Object monkeyObject5 = Object(&monkeyMesh, &stoneMaterial, Transform({ 0, 2, 0 }, { 0.3f, 0.3f, 0.3f }, { 0, 0, 0 }), "small right monkey");

	FPSText = TextObject(10, 10, GLUT_BITMAP_9_BY_15, "0", Vector3f(0, 1, 0));

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

	sceneGraph.InsertRootNode(new SceneGraphNode(&objects[0]));
	SceneGraphNode* node2 = sceneGraph.InsertNode(sceneGraph.GetRootNode(), new SceneGraphNode(&objects[1]));
	SceneGraphNode* node = sceneGraph.InsertNode(sceneGraph.GetRootNode(), new SceneGraphNode(&objects[2]));
	sceneGraph.InsertNode(node, new SceneGraphNode(&objects[3]));
	sceneGraph.InsertNode(node2, new SceneGraphNode(&objects[4]));

	textObjects = {&FPSText, &ObjectNameText, &TransformText, &PositionText, &ScaleText, &RotationText};

	ObjectNameText.text = objects[focusObjectIndex].name;
	UpdateTransformationText();
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