#include "Application.h"

Application::Application(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutCreateWindow("Simple OpenGL Program");
	glutInitWindowSize(800, 800);
	glutDisplayFunc(GLUTCallbacks::Display);
	glutMainLoop();
}

Application::~Application()
{

}

void Application::Update()
{

	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW); // Select model-view matrix
	glLoadIdentity(); // Reset to identity matrix

	// Apply transformations (order is reversed due to stack nature)
	//glTranslatef(0.0f, 0.0f, -5.0f); // Move the object back
	glRotatef(45.0f, 0.0f, 1.0f, 0.0f); // Rotate around Y-axis
	glScalef(1.0f, 2.0f, 1.0f); // Scale the object

	// Draw the object
	GLfloat vertices[] = {
	 0.0f,  1.0f, 0.0f,  // Vertex 0
	-1.0f, -1.0f, 0.0f,  // Vertex 1
	 1.0f, -1.0f, 0.0f,  // Vertex 2
	 0.0f, -1.0f, 1.0f   // Vertex 3 (extra for fun)
	};

	GLubyte indices[] = {
		0, 1, 2,  // Triangle 1
		1, 2, 3   // Triangle 2
	};

	glEnableClientState(GL_VERTEX_ARRAY); // Enable vertex arrays
	glVertexPointer(3, GL_FLOAT, 0, vertices); // Point to vertex data

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices); // Draw indexed triangles

	glDisableClientState(GL_VERTEX_ARRAY); // Cleanup

	glFlush();
}