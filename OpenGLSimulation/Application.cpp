#include "Application.h"

Application::Application(int argc, char* argv[])
{
	Init(argc, argv);
	LoadScene();
	camera = Camera({0, 0, 8}, {0, 0, 0}, {0, 1, 0});
	MainLoop();
}

Application::~Application()
{

}

void Application::Init(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);

	//Window Initalization
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("Simple OpenGL Program");

	//GL Settings
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);
	//glEnable(GL_NORMALIZE);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor3f(1.0f, 1.0f, 1.0f);

	// Set Light Data
	Renderer::SetLight(&light);
}

void Application::LoadScene()
{
	FileLoader::LoadMeshFromOBJ("res/Mesh/monkey.obj", monkeyMesh);
	FileLoader::LoadTextureFromRAW("res/Texture/Penguins.raw", 512, 512, penguinTexture);


	objects.push_back(Object(&monkeyMesh, &penguinMaterial, Transform({ 2, 0, 0 }, { 0.3f, 0.3f, 0.3f }, { 0, 0, 0 }), "monkey"));
	objects.push_back(Object(&monkeyMesh, &penguinMaterial, Transform({ -2, 0, 0 }, { 0.3f, 0.3f, 0.3f }, { 0, 0, 0 })));
	objects.push_back(Object(&monkeyMesh, &penguinMaterial, Transform({ -5, 1, 0 }, { 0.3f, 0.3f, 0.3f }, { 0, 0, 0 })));
	objects.push_back(Object(&monkeyMesh, &penguinMaterial, Transform({ 4, -1, 3 }, { 0.3f, 0.3f, 0.3f }, { 0, 0, 0 }), "monkey 2"));
	objects.push_back(Object(&monkeyMesh, &penguinMaterial, Transform({ 2, 4, 1 }, { 0.3f, 0.3f, 0.3f }, { 0, 0, 0 })));

	FPSText = TextObject(10, SCREEN_HEIGHT - 25, GLUT_BITMAP_9_BY_15, "0", Vector3f(0, 1, 0));
	ObjectNameText = TextObject(10, 10, GLUT_BITMAP_9_BY_15, objects[0].name, Vector3f(0, 1, 0));

	light = { {1, 1, 1, 0}, {1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1} };
	penguinMaterial = Material(&penguinTexture, {1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}, 1000);


	//testImage = Object2D(nullptr, Transform2D({ 500, 500 }, { 100, 100 },45), Color(0, 0, 1, 0.5f));
}

void Application::MainLoop()
{
	//Callbacks
	glutKeyboardFunc(GLUTCallbacks::KeyboardDown);
	glutKeyboardUpFunc(GLUTCallbacks::KeyboardUp);
	glutMouseFunc(GLUTCallbacks::HandleMouseButtonPressed);
	glutPassiveMotionFunc(GLUTCallbacks::HandleMouseMove);
	glutMotionFunc(GLUTCallbacks::HandleMouseMove);
	
	glutDisplayFunc(GLUTCallbacks::Display);

	glutTimerFunc(REFRESH_RATE_DELAY, GLUTCallbacks::Timer, REFRESH_RATE_DELAY);

	//Mainloop

	glutMainLoop();
}

void Application::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for(Object object : objects)
		Renderer::RenderObject(object, camera, NULL);

	Renderer::RenderObject(objects[objectFocusIndex], camera, RenderFlags::WIREFRAME);

	Renderer::RenderTextObject(FPSText);
	Renderer::RenderTextObject(ObjectNameText);

	glFlush();
	glutSwapBuffers();
}

void Application::Update()
{
	glutPostRedisplay();
	
	FPSText.text = std::to_string((int)floor(1000 / (glutGet(GLUT_ELAPSED_TIME) - lastFrameTime)));
	lastFrameTime = glutGet(GLUT_ELAPSED_TIME);

	camera.Update(glutGet(GLUT_ELAPSED_TIME));
	if(Mouse::GetMouseButtonState(MouseButton::LEFT) == 0)
		camera.rotationRadius -= 0.1f;
	else if(Mouse::GetMouseButtonState(MouseButton::RIGHT) == 0)
		camera.rotationRadius += 0.1f;

	camera.SetFocus(objects[objectFocusIndex]);
}

void Application::SwitchObjectFocus()
{
	objectFocusIndex += 1;
	if (objectFocusIndex >= objects.size())
		objectFocusIndex -= objects.size();
	ObjectNameText.text = objects[objectFocusIndex].name;
}

void Application::HandleKeyboardDown(unsigned char key, int x, int y)
{
	Keyboard::SetButtonPressedDown(key);
	if(key == ' ')
		SwitchObjectFocus();
}
void Application::HandleKeyboardUp(unsigned char key, int x, int y)
{
	Keyboard::SetButtonReleased(key);
}

void Application::HandleMouseButtonPressed(int button, int state, int x, int y)
{
	Mouse::SetMouseButtonState(button, state);
}
void Application::HandleMouseMove(int x, int y)
{
	Mouse::SetMousePosition(x, y);
}


