#include "Car.h"


Car::Car()
{
	//boundingBox = glm::vec3(2, 2, 2);
	node = new Node(this);
}


Car::~Car()
{

}

void Car::Initialize()
{
	GameObject::Initialize();
	this->LoadModel("Resources\\Models\\Car", "BMW.obj");

	if (m_oModel == NULL)
	{
		printf("Could not load car model!\n");
	}
}

void Car::Render(GLuint shaderID)
{
	GameObject::Render(shaderID);

	if (m_oModel)
	{
		m_oModel->Render(shaderID);
	}
	else
	{
		printf("Could not load car model!\n");
	}
}

void Car::Update(GLfloat deltaTime)
{
	GameObject::Update(deltaTime);
	//Render(shaderID);

	boundingBox.left = this->node->m_vPosition.x - 1;
	boundingBox.right = this->node->m_vPosition.x + 1;
	boundingBox.up = this->node->m_vPosition.y + 2;
	boundingBox.down = this->node->m_vPosition.y - 2;
	boundingBox.front = this->node->m_vPosition.z - 4;
	boundingBox.back = this->node->m_vPosition.z + 4;
}