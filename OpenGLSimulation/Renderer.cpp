#include "Renderer.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::RenderObject(Object& object, Camera& camera, int flags)
{
	// Test if the Mesh is loaded

	if (object.mesh == nullptr)
		return;

	// Set the perspective

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	gluPerspective(45.0f, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.01f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Set the Camera direction

	gluLookAt(camera.eye.x, camera.eye.y, camera.eye.z, camera.center.x, camera.center.y, camera.center.z, camera.up.x, camera.up.y, camera.up.z);

	// Apply Transformations

	glTranslatef(object.transform.Position.x, object.transform.Position.y, object.transform.Position.z);
	
	glRotatef(object.transform.Rotation.z, 0.0f, 0.0f, 1.0f);
	glRotatef(object.transform.Rotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef(object.transform.Rotation.x, 1.0f, 0.0f, 0.0f);

	glScalef(object.transform.Scale.x, object.transform.Scale.y, object.transform.Scale.z);

	// Push the mesh date to the GPU

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, &object.mesh->vertices[0].x);

	if (flags == RenderFlags::WIREFRAME)
	{
		glColor3f(0, 1, 0);
		glDrawElements(GL_LINES, object.mesh->indices.size(), GL_UNSIGNED_INT, object.mesh->indices.data());
		glColor3f(1, 1, 1);
	}
	else
	{
		glDrawElements(GL_TRIANGLES, object.mesh->indices.size(), GL_UNSIGNED_INT, object.mesh->indices.data());
	}

	glDisableClientState(GL_VERTEX_ARRAY);
}

void Renderer::Render2DObject(Object2D& object)
{

}

void Renderer::RenderTextObject(TextObject& textObject)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	const char* character;

	glColor3f(textObject.color.x, textObject.color.y, textObject.color.z);

	glRasterPos2f(textObject.screenX, textObject.screenY);
	for (character = textObject.text.c_str(); *character != '\0'; character++)
		glutBitmapCharacter(textObject.font, *character);
	glColor3f(1, 1, 1);
}