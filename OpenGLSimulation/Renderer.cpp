#include "Renderer.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::RenderMesh(Mesh& mesh, Camera& camera, float rot)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRotatef(-90, 1, 0, 0);
	glRotatef(rot, 0, 0, 1);
	glScalef(0.2f, 0.2f, 0.2f);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, &mesh.vertices[0].x);

	glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, mesh.indices.data());

	glDisableClientState(GL_VERTEX_ARRAY);
}
