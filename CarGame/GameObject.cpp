#include "GameObject.h"


GameObject::GameObject()
	:m_oModel(NULL),
	isInitialized(false)
{
	boundingBox.left = 0;
	boundingBox.right = 0;
	boundingBox.up = 0;
	boundingBox.down = 0;
	boundingBox.front = 0;
	boundingBox.back = 0;

}

GameObject::~GameObject()
{

}

void GameObject::LoadModel(char* path, char* modelName)
{
	m_oModel = new Model(path, modelName);
}

void GameObject::Initialize()
{
	isInitialized = true;

}

void GameObject::Render(GLuint shaderID)
{
	if (!isInitialized)
		Initialize();
}

void GameObject::Update(GLfloat deltaTime)
{
	
}



