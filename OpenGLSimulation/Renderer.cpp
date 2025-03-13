#include "Renderer.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::RenderMesh(Object& object, Camera& camera)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)1280 / (float)720, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(object.transform.Position.x, object.transform.Position.y, object.transform.Position.z);
	
	glRotatef(object.transform.Rotation.z, 0.0f, 0.0f, 1.0f);
	glRotatef(object.transform.Rotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef(object.transform.Rotation.x, 1.0f, 0.0f, 0.0f);

	glScalef(object.transform.Scale.x, object.transform.Scale.y, object.transform.Scale.z);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, &object.mesh->vertices[0].x);

	glDrawElements(GL_TRIANGLES, object.mesh->indices.size(), GL_UNSIGNED_INT, object.mesh->indices.data());

	glDisableClientState(GL_VERTEX_ARRAY);
}
