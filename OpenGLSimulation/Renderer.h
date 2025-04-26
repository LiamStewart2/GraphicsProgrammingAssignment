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
#include "Light.h"
#include "Scene.h"


enum RenderFlags
{
	WIREFRAME = 0x01
};

class Renderer
{
public:
	Renderer();
	~Renderer();

	static void RenderScene(Scene& scene);
	static void RenderSceneGraphNode(Scene& scene, SceneGraphNode* sceneGraphNode);

	static void RenderObject(Object* object, const Camera* camera, int flags);
	static void Render2DObject(Object2D& object);
	static void RenderTextObject(TextObject* textObject);

	static void SetMaterial(Material* material);
	static void SetLight(Light* light);

	static void ResetMaterial();
};

