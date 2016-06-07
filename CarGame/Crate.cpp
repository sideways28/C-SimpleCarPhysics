#include "Crate.h"


Crate::Crate()
{
	node = new Node(this);
}


Crate::~Crate()
{
}

void Crate::Initialize()
{
	GameObject::Initialize();

	this->LoadModel("Resources\\Models\\Misc", "Crate.obj");

	if (m_oModel == NULL)
	{
		printf("Could not load Crate model!\n");
	}
}

void Crate::Render(GLuint shaderID)
{
	GameObject::Render(shaderID);

	if (m_oModel)
	{
		m_oModel->Render(shaderID);
	}
	else
	{
		printf("Could not load Crate model!\n");
	}
}

void Crate::Update(GLfloat deltaTime)
{
	GameObject::Update(deltaTime);
	//Render(shaderID);

	boundingBox.left = this->node->m_vPosition.x - this->node->m_vSize.x / 2;
	boundingBox.right = this->node->m_vPosition.x + this->node->m_vSize.x / 2;
	boundingBox.up = this->node->m_vPosition.y + this->node->m_vSize.y / 2;
	boundingBox.down = this->node->m_vPosition.y - this->node->m_vSize.y / 2;
	boundingBox.front = this->node->m_vPosition.z - this->node->m_vSize.z / 2;
	boundingBox.back = this->node->m_vPosition.z + this->node->m_vSize.z / 2;
}
