#include "Renderer.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

// Set the perspective matrix and initalize the model matrix
void Renderer::RenderScene(Scene& scene)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	gluPerspective(45.0f, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.01f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Camera* camera = scene.GetCamera();
	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->center.x, camera->center.y, camera->center.z, camera->up.x, camera->up.y, camera->up.z);

	RenderSceneGraphNode(scene, scene.GetSceneGraph()->GetRootNode());
	SetLight(scene.GetLight());

	Renderer::ResetMaterial();

	std::vector<TextObject*>* textObjects = scene.GetTextObjectBuffer();
	for(int i = 0; i < textObjects->size(); i++)
		RenderTextObject(textObjects->at(i));

}

// Use recursion to iterate through the SceneGraph
void Renderer::RenderSceneGraphNode(Scene& scene, SceneGraphNode* sceneGraphNode)
{
	glPushMatrix();

	Renderer::RenderObject(sceneGraphNode->GetNodeObject(), scene.GetCamera(), NULL);

	if (sceneGraphNode->GetNodeObject() == scene.GetFocusObject())
	{
		Renderer::RenderObject(sceneGraphNode->GetNodeObject(), scene.GetCamera(), RenderFlags::WIREFRAME);    
	}
	
	glPushMatrix();

	for (int i = 0; i < sceneGraphNode->GetNumberOfChildNodes(); i++)
		RenderSceneGraphNode(scene, sceneGraphNode->GetChildNode(i));
	glPopMatrix();
}

// Render Individual Objects, will only work with scene rendering due to needing matricies loaded
void Renderer::RenderObject(Object* object, const Camera* camera, int flags)
{
	// Test if the Mesh is loaded
	if (object->mesh == nullptr)
		return;

	// Apply Transformations if not a wireframe
	if(flags != RenderFlags::WIREFRAME)
	{
		glTranslatef(object->transform.Position.x, object->transform.Position.y, object->transform.Position.z);

		glRotatef(object->transform.Rotation.z, 0.0f, 0.0f, 1.0f);
		glRotatef(object->transform.Rotation.y, 0.0f, 1.0f, 0.0f);
		glRotatef(object->transform.Rotation.x, 1.0f, 0.0f, 0.0f);

		glScalef(object->transform.Scale.x, object->transform.Scale.y, object->transform.Scale.z);

		// Bind texture

		object->material->texture->BindTexture();
		Renderer::SetMaterial(object->material);
	}

	// Push the mesh date to the GPU

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, &object->mesh->vertexPositions[0].x);
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 0, &object->mesh->vertexNormals[0].x);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, &object->mesh->vertexTextureCoordinates[0].x);

	if (flags == RenderFlags::WIREFRAME)
	{
		glDisable(GL_LIGHTING);
		glEnable(GL_COLOR_MATERIAL);
		
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		glColor3f(0, 1, 0);
		glDrawElements(GL_TRIANGLES, object->mesh->faces.size(), GL_UNSIGNED_INT, object->mesh->faces.data());
		glColor3f(1, 1, 1);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glEnable(GL_LIGHTING);
		glDisable(GL_COLOR_MATERIAL);
	}
	else
	{
		glDrawElements(GL_TRIANGLES, object->mesh->faces.size(), GL_UNSIGNED_INT, object->mesh->faces.data());
	}

	// Unbind texture

	object->material->texture->UnbindTexture();

	// GL Disable
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Renderer::Render2DObject(Object2D& object)
{
	// Set the perspective
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Disable OpenGL functionality

	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	// Enable OpenGL functionality

	glEnable(GL_COLOR_MATERIAL);

	// Transformations

	glTranslatef(object.transform.Position.x, object.transform.Position.y, 0);

	glRotatef(object.transform.Rotation, 0.0f, 0.0f, 1.0f);

	glScalef(object.transform.Scale.x, object.transform.Scale.y, 1);

	// Push the sprite data to the GPU
	glColor4f(object.color.r, object.color.g, object.color.b, object.color.a);
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 0); glVertex3f(0, 1, 0); glVertex3f(1, 1, 0); glVertex3f(1, 0, 0);
	glEnd();
	glColor4f(1, 1, 1, 1);

	// Enable OpenGL functionality

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	// Disable OpenGL functionality

	glDisable(GL_COLOR_MATERIAL);
}

void Renderer::RenderTextObject(TextObject* textObject)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

	const char* character;

	glColor3f(textObject->color.x, textObject->color.y, textObject->color.z);

	glRasterPos2f(textObject->screenX, textObject->screenY);
	for (character = textObject->text.c_str(); *character != '\0'; character++)
		glutBitmapCharacter(textObject->font, *character);
	glColor3f(1, 1, 1);

	glEnable(GL_LIGHTING);
	glDisable(GL_COLOR_MATERIAL);
}

void Renderer::SetMaterial(Material* material)
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, &material->ambient.x);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, &material->diffuse.x);
	glMaterialfv(GL_FRONT, GL_SPECULAR, &material->specular.x);

	glMaterialf(GL_FRONT, GL_SHININESS, material->shininess);
}

void Renderer::ResetMaterial()
{
	float ambient[4] = { 0.2, 0.2, 0.2, 1.0 };
	float diffuse[4] = { 0.8, 0.8, 0.8, 1.0 };
	float specular[4] = { 0.0, 0.0, 0.0, 1.0 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

	glMaterialf(GL_FRONT, GL_SHININESS, 100);
}

void Renderer::SetLight(Light* light)
{
	glMatrixMode(GL_MODELVIEW);

	glLightfv(GL_LIGHT0, GL_POSITION, &light->position.x);

	glLightfv(GL_LIGHT0, GL_AMBIENT, &light->ambient.x);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &light->diffuse.x);
	glLightfv(GL_LIGHT0, GL_SPECULAR, &light->specular.x);

}