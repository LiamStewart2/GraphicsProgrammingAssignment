#pragma once

#include <Windows.h>

#include <GL/GL.h>
#include <GL/GLU.h>
#include "GL/freeglut.h"

#include "Globals.h"
#include "Object.h"
#include "Object2D.h"
#include "TextObject.h"
#include "Camera.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	static void RenderObject(Object& object, Camera& camera, int flags);
	static void Render2DObject(Object2D& object);
	static void RenderTextObject(TextObject& textObject);
};

