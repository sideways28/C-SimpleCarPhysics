#pragma once
#include "Node.h"

class Node;
class Scene
{
private:
	Node* m_oRootNode;
public:
	Scene();
	~Scene();
	
	Node* GetRootNode();
	void Update(GLfloat deltaTime);
};

