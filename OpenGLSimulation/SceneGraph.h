#pragma once

#include <vector>

#include "Object.h"

// The scene graph node
//stores a vector of other nodes, each storing an object
class SceneGraphNode
{
public:
	SceneGraphNode(Object* _object) : object(_object), nodes(std::vector<SceneGraphNode*>()) {}

	SceneGraphNode* InsertNode(SceneGraphNode* childNode) 
	{ 
		nodes.push_back(childNode); 
		childNode->SetParentNode(this);
		return nodes[nodes.size() - 1];
	}

	Object* GetNodeObject() { return object; }
	SceneGraphNode* GetParentNode() { return parentNode; }

	int GetNumberOfChildNodes() { return nodes.size(); }
	SceneGraphNode* GetChildNode(int index) 
	{ 
		if(index < nodes.size())
			return nodes[index]; 
		return nullptr;
	}

	// Uses OpenGL Matrix function to recursively iterate the tree
	// and calculate the world object position of each object
	void UpdateObjectWorldPosition()
	{
		glPushMatrix();

		glTranslatef(object->transform.Position.x, object->transform.Position.y, object->transform.Position.z);

		glRotatef(object->transform.Rotation.z, 0.0f, 0.0f, 1.0f);
		glRotatef(object->transform.Rotation.y, 0.0f, 1.0f, 0.0f);
		glRotatef(object->transform.Rotation.x, 1.0f, 0.0f, 0.0f);

		glScalef(object->transform.Scale.x, object->transform.Scale.y, object->transform.Scale.z);

		GLfloat model[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, model);

		// Find the world Position
		object->worldTransform.Position = Vector3f({ model[12], model[13], model[14] });

		// Find the world Scale
		Vector3f scale = {
			sqrt(model[0] * model[0] + model[1] * model[1] + model[2] * model[2]),   // X scale
			sqrt(model[4] * model[4] + model[5] * model[5] + model[6] * model[6]),   // Y scale
			sqrt(model[8] * model[8] + model[9] * model[9] + model[10] * model[10])  // Z scale
		};

		object->worldTransform.Scale = scale;

		for(SceneGraphNode* node : nodes)
			node->UpdateObjectWorldPosition();

		glPopMatrix();
	}

	void SetParentNode(SceneGraphNode* parent) {parentNode = parent;}

private:
	Object* object = nullptr;

	SceneGraphNode* parentNode = nullptr;
	std::vector<SceneGraphNode*> nodes;
};

class SceneGraph
{
public:
	SceneGraph() {};

	void InsertRootNode(SceneGraphNode* rootChildNode)
	{
		root = rootChildNode;
		root->SetParentNode(nullptr);
	}

	SceneGraphNode* InsertNode(SceneGraphNode* parentNode, SceneGraphNode* childNode)
	{
		return parentNode->InsertNode(childNode);
	}

	// Uses OpenGL Matrix functions to calculate the world position of each object
	void UpdateObjectWorldPositions()
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		root->UpdateObjectWorldPosition();
	}

	Object* GetRootObject() { return root->GetNodeObject(); }
	SceneGraphNode* GetRootNode() { return root; }

private:
	SceneGraphNode* root = nullptr;
};