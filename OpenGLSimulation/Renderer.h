#pragma once

#include <Windows.h>

#include <GL/GL.h>
#include <GL/GLU.h>
#include "GL/freeglut.h"

#include "Globals.h"
#include "Object.h"
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

	void RenderScene(Scene& scene);
private:
	void RenderSceneGraphNode(Scene& scene, SceneGraphNode* sceneGraphNode);
	
	void RenderObject(Object* object, const Camera* camera, int flags);
	void RenderTextObject(TextObject* textObject);

	void SetMaterial(Material* material);
	void SetLight(Light* light);

	void ResetMaterial();
};