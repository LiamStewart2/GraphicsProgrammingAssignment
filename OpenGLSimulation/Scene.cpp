#include "Scene.h"

Scene::Scene()
{
	focusObjectIndex = 0;
	camera = Camera({ 0, 2, 8 }, { 0, 0, 0 }, { 0, 1, 0 });
}

Scene::~Scene()
{
	for(int i = 0; i < textObjects.size(); i++)
		delete textObjects[i];
}

void Scene::InitScene()
{
	light = { {1, 1, 1, 0}, {0.3f, 0.3f, 0.3f, 1}, {0.7f, 0.7f, 0.7f, 1}, {0.5f, 0.5f, 0.5f, 1} };

	// Load All Assets
	FileLoader::LoadMeshFromOBJ("res/Mesh/monkey.obj", monkeyMesh);
	FileLoader::LoadMeshFromOBJ("res/Mesh/ground.obj", groundMesh);
	FileLoader::LoadMeshFromOBJ("res/Mesh/donut.obj", donutMesh);

	FileLoader::LoadTextureFromBMP("res/Texture/stone.bmp", stoneTexture);
	FileLoader::LoadTextureFromBMP("res/Texture/grass.bmp", grassTexture);
	FileLoader::LoadTextureFromRAW("res/Texture/Penguins.raw", 512, 512, penguinTexture);

	// Build all materials
	stoneMaterial = Material(&stoneTexture, { 1, 1, 1, 1 }, { 1, 1, 1, 1 }, { 1, 1, 1, 1 }, 64);
	grassMaterial = Material(&grassTexture, { 0.2, 0.2, 0.2, 1 }, { 0.5, 1, 0.5, 1 }, { 1, 1, 1, 1 }, 64);
	penguinMaterial = Material(&penguinTexture, {0.4, 0.4, 0.4, 1}, {0.8, 0.8, 0.8, 1}, {1, 1, 1, 1}, 64);

	// Build the current objects to push to the scene graph
	Object* groundObject =	new Object(&groundMesh, &grassMaterial,  Transform({ 0, 0, 0 }, { 0.2f, 0.2f, 0.2f}, { 0, 0, 0 }), "ground");
	Object* donut =			new Object(&donutMesh, &penguinMaterial,  Transform({ 0, 2, 8 }, { 1, 1, 1}, { 0, 0, 0 }), "donut");
	Object* monkeyObject =	new BouncingObject(&monkeyMesh, &stoneMaterial, Transform({0, 0, 0}, {1, 1, 1}, {0, 0, 0}), "Big monkey");
	Object* monkeyObject2 = new SpinningObject(&monkeyMesh, &stoneMaterial, Transform({6, 0, 0}, {1, 1, 1}, {0, 0, 0}), "Right monkey");
	Object* monkeyObject3 = new Object(&monkeyMesh, &stoneMaterial, Transform({-2, 0, 0}, {0.5f, 0.5f, 0.5f}, {0, 0, 0}), "Left monkey");
	Object* monkeyObject4 = new Object(&monkeyMesh, &stoneMaterial, Transform({0, 2, 0}, {0.5f, 0.5f, 0.5f}, {0, 0, 0}), "small left monkey : )");
	Object* monkeyObject5 = new Object(&monkeyMesh, &stoneMaterial, Transform({ 0, 2, 0 }, { 0.35f, 0.35f, 0.35f }, { 0, 0, 0 }), "small right monkey");
	Object* monkeyObject6 = new Object(&monkeyMesh, &stoneMaterial, Transform({ 4, 0, 0 }, { 1, 1, 1 }, { 0, 0, 0 }), "same size right monkey");

	// Build all text Objects
	FPSText = TextObject(10, 10, GLUT_BITMAP_9_BY_15, "0", Vector3f(0, 1, 0));
	instructionsText = TextObject(SCREEN_WIDTH - 250, 10, GLUT_BITMAP_9_BY_15, "Controls on the README.md", Vector3f(0, 1, 0));

	ObjectNameText = TextObject(SCREEN_WIDTH - 250, SCREEN_HEIGHT - 15, GLUT_BITMAP_9_BY_15, "", Vector3f(0, 1, 0));
	TransformText = TextObject(SCREEN_WIDTH - 250, SCREEN_HEIGHT - 30, GLUT_BITMAP_9_BY_15, "Translate - X", Vector3f(0, 1, 0));

	PositionText = TextObject(SCREEN_WIDTH - 250, SCREEN_HEIGHT - 45, GLUT_BITMAP_9_BY_15, "Position x, y, z", Vector3f(0, 1, 0));
	ScaleText = TextObject(SCREEN_WIDTH - 250, SCREEN_HEIGHT - 60, GLUT_BITMAP_9_BY_15, "Scale x, y, z", Vector3f(0, 1, 0));
	RotationText = TextObject(SCREEN_WIDTH - 250, SCREEN_HEIGHT - 75, GLUT_BITMAP_9_BY_15, "Rotation x, y, z", Vector3f(0, 1, 0));

	// Push objects to the linked list
	objects.Push(groundObject);
	objects.Push(monkeyObject);
	objects.Push(monkeyObject2);
	objects.Push(monkeyObject3);
	objects.Push(monkeyObject4);
	objects.Push(monkeyObject5);
	objects.Push(monkeyObject6);
	objects.Push(donut);

	// load the scene graph
	sceneGraph.InsertRootNode(new SceneGraphNode(objects[0]));

	SceneGraphNode* rootMonkey1 = sceneGraph.InsertNode(sceneGraph.GetRootNode(), new SceneGraphNode(objects[1]));
	SceneGraphNode* rootMonkey2 = sceneGraph.InsertNode(sceneGraph.GetRootNode(), new SceneGraphNode(objects[2]));

	SceneGraphNode* secondRootMonkey2 = sceneGraph.InsertNode(rootMonkey1, new SceneGraphNode(objects[3]));

	sceneGraph.InsertNode(secondRootMonkey2, new SceneGraphNode(objects[4]));
	sceneGraph.InsertNode(rootMonkey2, new SceneGraphNode(objects[5]));
	sceneGraph.InsertNode(rootMonkey2, new SceneGraphNode(objects[6]));
	sceneGraph.InsertNode(sceneGraph.GetRootNode(), new SceneGraphNode(objects[7]));

	// compile a list of text objects to make iteration easier
	// doing it here so that it doesnt override the heiarchy
	textObjects = {&FPSText, &ObjectNameText, &TransformText, &PositionText, &ScaleText, &RotationText, &instructionsText};
	// build the text for the heirachy before loading the boids to reduce the text clutter on the screen
	BuildHierarchy();

	// Load 100 boids
	boids = std::vector<BoidObject*>();
	boids.resize(100);
	for (int i = 0; i < 100; i++)
	{
		BoidObject* boid = new BoidObject(&monkeyMesh, &stoneMaterial, Transform({ 30 + float(rand() % 50), float(rand() % 50), float(rand() % 50) }, {0.6f, 0.6f, 0.6f}, {0, 0, 0}));
		objects.Push(boid); boids[i] = boid;
		boid->SetReferenceToBoids(&boids);
		sceneGraph.InsertNode(sceneGraph.GetRootNode(), new SceneGraphNode(objects[objects.Size() - 1]));
	}

	// compile a list of materials to make iteration easier
	materials = {&stoneMaterial, &grassMaterial, &penguinMaterial};

	// misc
	ObjectNameText.text = objects[focusObjectIndex]->name;
	UpdateTransformationText();

	transformationManager.SetMaterials(&materials);
}

void Scene::Update()
{
	// handles input for the transformations
	transformationManager.Update(objects[focusObjectIndex]);

	UpdateObjects();

	// calculate fps
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	int deltaTime = currentTime - lastFrameTime;
	lastFrameTime = currentTime;

	if (deltaTime > 0)
		FPSText.text = std::to_string(1000 / deltaTime);

	lastFrameTime = glutGet(GLUT_ELAPSED_TIME);
	UpdateTransformTexts();

	// updates all world transformations for all objects
	sceneGraph.UpdateObjectWorldPositions();

	camera.Update();
}

void Scene::UpdateObjects()
{
	for (int i = 0; i < objects.Size(); i++)
		objects[i]->Update();
}

void Scene::UpdateTransformationText()
{
	std::string transformMode = transformationManager.getTransformModeText();
	std::string transformAxis = transformationManager.getTransformAxisText();

	TransformText.text = transformMode + " - " + transformAxis;
}

void Scene::UpdateTransformTexts()
{
	PositionText.text = "Position: " + objects[focusObjectIndex]->worldPosition.ToString();
	ScaleText.text = "Scale:    " + objects[focusObjectIndex]->transform.Scale.ToString();
	RotationText.text = "Rotation: " + objects[focusObjectIndex]->transform.Rotation.ToString();
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
		camera.TrackObject(objects[focusObjectIndex]);
	else
		camera.TrackObject(nullptr);
}

void Scene::ChangeFocusIndex()
{
	focusObjectIndex += 1;
	if (focusObjectIndex >= objects.Size())
		focusObjectIndex -= objects.Size();

	if(camera.IsObjectTracking())
		camera.TrackObject(objects[focusObjectIndex]);

	ObjectNameText.text = objects[focusObjectIndex]->name;
}