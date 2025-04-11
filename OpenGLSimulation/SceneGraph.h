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

	Object* GetRootObject() { return root->GetNodeObject(); }
	SceneGraphNode* GetRootNode() { return root; }

private:
	SceneGraphNode* root = nullptr;
};