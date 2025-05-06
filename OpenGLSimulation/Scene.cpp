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

	FileLoader::LoadMeshFromOBJ("res/Mesh/monkey.obj", monkeyMesh);
	FileLoader::LoadMeshFromOBJ("res/Mesh/ground.obj", groundMesh);
	FileLoader::LoadMeshFromOBJ("res/Mesh/donut.obj", donutMesh);

	FileLoader::LoadTextureFromBMP("res/Texture/stone.bmp", stoneTexture);
	FileLoader::LoadTextureFromBMP("res/Texture/grass.bmp", grassTexture);
	FileLoader::LoadTextureFromRAW("res/Texture/Penguins.raw", 512, 512, penguinTexture);

	stoneMaterial = Material(&stoneTexture, { 1, 1, 1, 1 }, { 1, 1, 1, 1 }, { 1, 1, 1, 1 }, 64);
	grassMaterial = Material(&grassTexture, { 0.2, 0.2, 0.2, 1 }, { 0.5, 1, 0.5, 1 }, { 1, 1, 1, 1 }, 64);
	penguinMaterial = Material(&penguinTexture, {0.4, 0.4, 0.4, 1}, {0.8, 0.8, 0.8, 1}, {1, 1, 1, 1}, 64);

	Object* groundObject =	new Object(&groundMesh, &grassMaterial,  Transform({ 0, 0, 0 }, { 0.2f, 0.2f, 0.2f}, { 0, 0, 0 }), "ground");
	Object* donut =			new Object(&donutMesh, &penguinMaterial,  Transform({ 0, 2, 8 }, { 1, 1, 1}, { 0, 0, 0 }), "donut");
	Object* monkeyObject =	new BouncingObject(&monkeyMesh, &stoneMaterial, Transform({0, 0, 0}, {1, 1, 1}, {0, 0, 0}), "Big monkey");
	Object* monkeyObject2 = new SpinningObject(&monkeyMesh, &stoneMaterial, Transform({6, 0, 0}, {1, 1, 1}, {0, 0, 0}), "Right monkey");
	Object* monkeyObject3 = new Object(&monkeyMesh, &stoneMaterial, Transform({-2, 0, 0}, {0.5f, 0.5f, 0.5f}, {0, 0, 0}), "Left monkey");
	Object* monkeyObject4 = new Object(&monkeyMesh, &stoneMaterial, Transform({0, 2, 0}, {0.5f, 0.5f, 0.5f}, {0, 0, 0}), "small left monkey : )");
	Object* monkeyObject5 = new Object(&monkeyMesh, &stoneMaterial, Transform({ 0, 2, 0 }, { 0.35f, 0.35f, 0.35f }, { 0, 0, 0 }), "small right monkey");
	Object* monkeyObject6 = new Object(&monkeyMesh, &stoneMaterial, Transform({ 4, 0, 0 }, { 1, 1, 1 }, { 0, 0, 0 }), "same size right monkey");

	FPSText = TextObject(10, 10, GLUT_BITMAP_9_BY_15, "0", Vector3f(0, 1, 0));
	instructionsText = TextObject(SCREEN_WIDTH - 250, 10, GLUT_BITMAP_9_BY_15, "Controls on the README.md", Vector3f(0, 1, 0));

	ObjectNameText = TextObject(SCREEN_WIDTH - 250, SCREEN_HEIGHT - 15, GLUT_BITMAP_9_BY_15, "", Vector3f(0, 1, 0));
	TransformText = TextObject(SCREEN_WIDTH - 250, SCREEN_HEIGHT - 30, GLUT_BITMAP_9_BY_15, "Translate - X", Vector3f(0, 1, 0));

	PositionText = TextObject(SCREEN_WIDTH - 250, SCREEN_HEIGHT - 45, GLUT_BITMAP_9_BY_15, "Position x, y, z", Vector3f(0, 1, 0));
	ScaleText = TextObject(SCREEN_WIDTH - 250, SCREEN_HEIGHT - 60, GLUT_BITMAP_9_BY_15, "Scale x, y, z", Vector3f(0, 1, 0));
	RotationText = TextObject(SCREEN_WIDTH - 250, SCREEN_HEIGHT - 75, GLUT_BITMAP_9_BY_15, "Rotation x, y, z", Vector3f(0, 1, 0));

	objects.Push(groundObject);
	objects.Push(monkeyObject);
	objects.Push(monkeyObject2);
	objects.Push(monkeyObject3);
	objects.Push(monkeyObject4);
	objects.Push(monkeyObject5);
	objects.Push(monkeyObject6);
	objects.Push(donut);

	sceneGraph.InsertRootNode(new SceneGraphNode(objects[0]));

	SceneGraphNode* rootMonkey1 = sceneGraph.InsertNode(sceneGraph.GetRootNode(), new SceneGraphNode(objects[1]));
	SceneGraphNode* rootMonkey2 = sceneGraph.InsertNode(sceneGraph.GetRootNode(), new SceneGraphNode(objects[2]));

	SceneGraphNode* secondRootMonkey2 = sceneGraph.InsertNode(rootMonkey1, new SceneGraphNode(objects[3]));

	sceneGraph.InsertNode(secondRootMonkey2, new SceneGraphNode(objects[4]));
	sceneGraph.InsertNode(rootMonkey2, new SceneGraphNode(objects[5]));
	sceneGraph.InsertNode(rootMonkey2, new SceneGraphNode(objects[6]));
	sceneGraph.InsertNode(sceneGraph.GetRootNode(), new SceneGraphNode(objects[7]));

	if(BOIDS)
	{
		boids = std::vector<BoidObject*>();
		boids.resize(100);
		for (int i = 0; i < 100; i++)
		{
			BoidObject* boid = new BoidObject(&monkeyMesh, &stoneMaterial, Transform({ float(rand() % 50), float(rand() % 50), float(rand() % 50) }, { 0.6f, 0.6f, 0.6f }, { 0, 0, 0 }));
			objects.Push(boid); boids[i] = boid;
			boid->SetReferenceToBoids(&boids);
			sceneGraph.InsertNode(sceneGraph.GetRootNode(), new SceneGraphNode(objects[objects.Size() - 1]));
		}
	}


	textObjects = {&FPSText, &ObjectNameText, &TransformText, &PositionText, &ScaleText, &RotationText, &instructionsText};
	materials = {&stoneMaterial, &grassMaterial, &penguinMaterial};

	ObjectNameText.text = objects[focusObjectIndex]->name;
	UpdateTransformationText();

	BuildHierarchy();

	transformationManager.SetMaterials(&materials);
}

void Scene::Update()
{
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

int InvertMatrix(const float m[16], float invOut[16]) {
	float inv[16], det;
	int i;

	inv[0] = m[5] * m[10] * m[15] -
		m[5] * m[11] * m[14] -
		m[9] * m[6] * m[15] +
		m[9] * m[7] * m[14] +
		m[13] * m[6] * m[11] -
		m[13] * m[7] * m[10];

	inv[4] = -m[4] * m[10] * m[15] +
		m[4] * m[11] * m[14] +
		m[8] * m[6] * m[15] -
		m[8] * m[7] * m[14] -
		m[12] * m[6] * m[11] +
		m[12] * m[7] * m[10];

	inv[8] = m[4] * m[9] * m[15] -
		m[4] * m[11] * m[13] -
		m[8] * m[5] * m[15] +
		m[8] * m[7] * m[13] +
		m[12] * m[5] * m[11] -
		m[12] * m[7] * m[9];

	inv[12] = -m[4] * m[9] * m[14] +
		m[4] * m[10] * m[13] +
		m[8] * m[5] * m[14] -
		m[8] * m[6] * m[13] -
		m[12] * m[5] * m[10] +
		m[12] * m[6] * m[9];

	inv[1] = -m[1] * m[10] * m[15] +
		m[1] * m[11] * m[14] +
		m[9] * m[2] * m[15] -
		m[9] * m[3] * m[14] -
		m[13] * m[2] * m[11] +
		m[13] * m[3] * m[10];

	inv[5] = m[0] * m[10] * m[15] -
		m[0] * m[11] * m[14] -
		m[8] * m[2] * m[15] +
		m[8] * m[3] * m[14] +
		m[12] * m[2] * m[11] -
		m[12] * m[3] * m[10];

	inv[9] = -m[0] * m[9] * m[15] +
		m[0] * m[11] * m[13] +
		m[8] * m[1] * m[15] -
		m[8] * m[3] * m[13] -
		m[12] * m[1] * m[11] +
		m[12] * m[3] * m[9];

	inv[13] = m[0] * m[9] * m[14] -
		m[0] * m[10] * m[13] -
		m[8] * m[1] * m[14] +
		m[8] * m[2] * m[13] +
		m[12] * m[1] * m[10] -
		m[12] * m[2] * m[9];

	inv[2] = m[1] * m[6] * m[15] -
		m[1] * m[7] * m[14] -
		m[5] * m[2] * m[15] +
		m[5] * m[3] * m[14] +
		m[13] * m[2] * m[7] -
		m[13] * m[3] * m[6];

	inv[6] = -m[0] * m[6] * m[15] +
		m[0] * m[7] * m[14] +
		m[4] * m[2] * m[15] -
		m[4] * m[3] * m[14] -
		m[12] * m[2] * m[7] +
		m[12] * m[3] * m[6];

	inv[10] = m[0] * m[5] * m[15] -
		m[0] * m[7] * m[13] -
		m[4] * m[1] * m[15] +
		m[4] * m[3] * m[13] +
		m[12] * m[1] * m[7] -
		m[12] * m[3] * m[5];

	inv[14] = -m[0] * m[5] * m[14] +
		m[0] * m[6] * m[13] +
		m[4] * m[1] * m[14] -
		m[4] * m[2] * m[13] -
		m[12] * m[1] * m[6] +
		m[12] * m[2] * m[5];

	inv[3] = -m[1] * m[6] * m[11] +
		m[1] * m[7] * m[10] +
		m[5] * m[2] * m[11] -
		m[5] * m[3] * m[10] -
		m[9] * m[2] * m[7] +
		m[9] * m[3] * m[6];

	inv[7] = m[0] * m[6] * m[11] -
		m[0] * m[7] * m[10] -
		m[4] * m[2] * m[11] +
		m[4] * m[3] * m[10] +
		m[8] * m[2] * m[7] -
		m[8] * m[3] * m[6];

	inv[11] = -m[0] * m[5] * m[11] +
		m[0] * m[7] * m[9] +
		m[4] * m[1] * m[11] -
		m[4] * m[3] * m[9] -
		m[8] * m[1] * m[7] +
		m[8] * m[3] * m[5];

	inv[15] = m[0] * m[5] * m[10] -
		m[0] * m[6] * m[9] -
		m[4] * m[1] * m[10] +
		m[4] * m[2] * m[9] +
		m[8] * m[1] * m[6] -
		m[8] * m[2] * m[5];

	det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

	if (det == 0)
		return 0;

	det = 1.0f / det;

	for (i = 0; i < 16; i++)
		invOut[i] = inv[i] * det;

	return 1;
}

void Scene::LeftClickPressed(int screenMouseX, int screenMouseY)
{
	Vector3f screenSpaceMouseCoordinates = Vector3f((float)screenMouseX / SCREEN_WIDTH * 2 - 1, 1 - (screenMouseY / (float)SCREEN_HEIGHT * 2), 1);
	Vector4f clipCoords = Vector4f(screenSpaceMouseCoordinates.x, screenSpaceMouseCoordinates.y, -1.0f, 1.0f);

	GLfloat projectionMatrix[16];
	glGetFloatv(GL_PROJECTION_MATRIX, projectionMatrix);
	GLfloat projectionInverse[16];
	InvertMatrix(projectionMatrix, projectionInverse);

	float rayEye[4];
	for (int i = 0; i < 4; i++) 
	{
		rayEye[i] = projectionInverse[i * 4 + 0] * clipCoords.x +
			projectionInverse[i * 4 + 1] * clipCoords.y +
			projectionInverse[i * 4 + 2] * clipCoords.z +
			projectionInverse[i * 4 + 3] * clipCoords.w;
	}

	GLfloat modelViewMatrix[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, modelViewMatrix);
	GLfloat modelViewInverse[16];
	InvertMatrix(modelViewMatrix, modelViewInverse);

	float rayWorld[4];
	for (int i = 0; i < 4; i++) {
		rayWorld[i] = modelViewInverse[i * 4 + 0] * rayEye[0] +
			modelViewInverse[i * 4 + 1] * rayEye[1] +
			modelViewInverse[i * 4 + 2] * rayEye[2] +
			modelViewInverse[i * 4 + 3] * rayEye[3];
	}

	float rayDirX = rayWorld[0];
	float rayDirY = rayWorld[1];
	float rayDirZ = rayWorld[2];
	float length = sqrt(rayDirX * rayDirX + rayDirY * rayDirY + rayDirZ * rayDirZ);

	rayDirX /= length;
	rayDirY /= length;
	rayDirZ /= length;
	
	float rayOrigin[3] = { camera.eye.x, camera.eye.y, camera.eye.z };
	float rayDirection[3] = { rayDirX, rayDirY, rayDirZ };

	std::cout << rayOrigin[0] << ", " << rayOrigin[1] << ", " << rayOrigin[2] << std::endl;
	std::cout << rayDirection[0] << ", " << rayDirection[1] << ", " << rayDirection[2] << std::endl;
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