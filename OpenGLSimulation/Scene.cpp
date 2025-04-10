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
	FileLoader::LoadMeshFromOBJ("res/Mesh/monkey.obj", monkeyMesh);

	FileLoader::LoadTextureFromBMP("res/Texture/stone.bmp", stoneTexture);

	stoneMaterial = Material(&stoneTexture, { 1, 1, 1, 1 }, { 1, 1, 1, 1 }, { 1, 1, 1, 1 }, 64);

	Object monkeyObject = Object(&monkeyMesh, &stoneMaterial, Transform({0, 0, 0}, {0.3f, 0.3f, 0.3f}, {0, 0, 0}));

	objects.push_back(monkeyObject);

	sceneGraph.InsertRootNode(new SceneGraphNode(&objects[0]));
}

void Scene::Update()
{
	camera.Update(glutGet(GLUT_ELAPSED_TIME));

	if (Mouse::GetMouseButtonState(MouseButton::LEFT) == 0)
		camera.rotationRadius -= 0.1f;
	else if (Mouse::GetMouseButtonState(MouseButton::RIGHT) == 0)
		camera.rotationRadius += 0.1f;

	camera.SetFocus(&objects[focusObjectIndex]);
}

std::string Scene::ChangeFocusIndex()
{
	focusObjectIndex += 1;
	if (focusObjectIndex >= objects.size())
		focusObjectIndex -= objects.size();
	return objects[focusObjectIndex].name;
}