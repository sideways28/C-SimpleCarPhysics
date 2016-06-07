#include "Wheel.h"


Wheel::Wheel()
{
	node = new Node(this);
}


Wheel::~Wheel()
{

}


void Wheel::Initialize()
{
	GameObject::Initialize();
	this->LoadModel("Resources\\Models\\Car", "policeCarWheel.obj");

	if (m_oModel == NULL)
	{
		printf("No Model Loaded\n!");
	}
}

void Wheel::Render(GLuint shaderID)
{
	GameObject::Render(shaderID);

	if (m_oModel)
	{
		m_oModel->Render(shaderID);
	}
	else
	{
		printf("No Model Loaded\n!");
	}
}

void Wheel::Update(GLfloat deltaTime)
{
	GameObject::Update(deltaTime);
	//Render(shaderID);
}


