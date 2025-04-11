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

	Object monkeyObject = Object(&monkeyMesh, &stoneMaterial, Transform({0, 0, 0}, {0.3f, 0.3f, 0.3f}, {0, 0, 0}));
	Object monkeyObject2 = Object(&monkeyMesh, &stoneMaterial, Transform({2, 0, 0}, {0.3f, 0.3f, 0.3f}, {0, 0, 0}));
	Object monkeyObject3 = Object(&monkeyMesh, &stoneMaterial, Transform({-2, 0, 0}, {0.3f, 0.3f, 0.3f}, {0, 0, 0}));
	Object monkeyObject4 = Object(&monkeyMesh, &stoneMaterial, Transform({0, 2, 0}, {0.3f, 0.3f, 0.3f}, {0, 0, 0}));

	objects.push_back(monkeyObject);
	objects.push_back(monkeyObject2);
	objects.push_back(monkeyObject3);
	objects.push_back(monkeyObject4);

	sceneGraph.InsertRootNode(new SceneGraphNode(&objects[0]));
	sceneGraph.InsertNode(sceneGraph.GetRootNode(), new SceneGraphNode(&objects[1]));
	SceneGraphNode* node = sceneGraph.InsertNode(sceneGraph.GetRootNode(), new SceneGraphNode(&objects[2]));
	sceneGraph.InsertNode(node, new SceneGraphNode(&objects[3]));
}

void Scene::Update()
{
	camera.Update();

	objects[0].transform.Position.y = sin(glutGet(GLUT_ELAPSED_TIME) * 0.001) * 0.25;
	objects[1].transform.Rotation.y = sin(glutGet(GLUT_ELAPSED_TIME) * 0.001) * 180;
	objects[2].transform.Rotation.z = sin(glutGet(GLUT_ELAPSED_TIME) * 0.0005) * 180;
}

void Scene::ToggleCameraObjectFocus()
{
	if(camera.IsObjectTracking() == false)
		camera.TrackObject(&objects[focusObjectIndex]);
	else
		camera.TrackObject(nullptr);
}

std::string Scene::ChangeFocusIndex()
{
	focusObjectIndex += 1;
	if (focusObjectIndex >= objects.size())
		focusObjectIndex -= objects.size();

	if(camera.IsObjectTracking())
		camera.TrackObject(&objects[focusObjectIndex]);

	return objects[focusObjectIndex].name;
}