#include "Scene.h"


Scene::Scene()
{
	m_oRootNode = new Node();
	m_oRootNode->SetNodeName("Scene RootNode");
}


Scene::~Scene()
{

}

Node* Scene::GetRootNode()
{
	return m_oRootNode;
}

void Scene::Update(GLfloat deltaTime)
{
	if (m_oRootNode)
		m_oRootNode->Update(deltaTime);
}
