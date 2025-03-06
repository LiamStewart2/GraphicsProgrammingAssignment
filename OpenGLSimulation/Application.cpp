#include "Application.h"

Application::Application(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("Simple OpenGL Program");
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
	glScalef(0.25f, 0.25f, 0.25f); // Scale the object

	// Draw the object
	GLfloat vertices[] = {
	 -1.0f,  1.0f, 0.0f, 1, 0, 0,  // Vertex 0
	  1.0f,  1.0f, 0.0f, 1, 1, 0,  // Vertex 1
	 -1.0f, -1.0f, 0.0f, 1, 0, 1,  // Vertex 2
	  1.0f, -1.0f, 0.0f, 1, 0, 0   // Vertex 3 (extra for fun)
	};

	GLubyte indices[] = {
		0, 1, 2,  // Triangle 1
		1, 2, 3   // Triangle 2
	};

	glEnableClientState(GL_VERTEX_ARRAY); // Enable vertex arrays
	glEnableClientState(GL_COLOR_ARRAY); // Enable Color arrays

	glVertexPointer(3, GL_FLOAT, 6 * sizeof(GLfloat), vertices); // Point to vertex data
	glColorPointer(3, GL_FLOAT, 6 * sizeof(GLfloat), vertices + 3); // Point to vertex data

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices); // Draw indexed triangles

	glDisableClientState(GL_VERTEX_ARRAY); // Cleanup
	glDisableClientState(GL_COLOR_ARRAY); // Cleanup

	glFlush();
}