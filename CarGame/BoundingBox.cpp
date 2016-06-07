#include "BoundingBox.h"


BoundingBox::BoundingBox()
	:fall(false)
{
	node = new Node(this);
	color = glm::vec3(1);
}


BoundingBox::~BoundingBox()
{
}

void BoundingBox::Initialize()
{
	left = -this->node->m_vSize.x / 2;
	right = this->node->m_vSize.x / 2;
	up = this->node->m_vSize.y / 2;
	down = -this->node->m_vSize.y / 2;
	front = -this->node->m_vSize.z / 2;
	back = this->node->m_vSize.z / 2;

	GameObject::Initialize();

	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);

	GLfloat vertices[] =
	{
		-0.5f, -0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,

		-0.5f, -0.5f, -0.5f,
		-0.5f, 0.5f, -0.5f,
		0.5f, 0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
	};

	GLint indices[] =
	{
		0, 3, 2,
		2, 1, 0,

		3, 7, 6, 
		6, 2, 3,

		7, 4, 5, 
		5, 6, 7,

		4, 0, 1,
		1, 5, 4,

		1, 2, 6,
		6, 5, 1,

		4, 7, 3,
		3, 0, 4
	};

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices[0], GL_STATIC_DRAW_ARB);

	glBindVertexArray(0);
}

void BoundingBox::Render(GLuint shaderID)
{
	GameObject::Render(shaderID);

	glUniform1i(glGetUniformLocation(shaderID, "material.texCount"), 0);
	glUniform3f(glGetUniformLocation(shaderID, "material.ambient"), color.x, color.y, color.z);
	glUniform3f(glGetUniformLocation(shaderID, "material.diffuse"), color.x, color.y, color.z);
	glUniform3f(glGetUniformLocation(shaderID, "material.specular"), color.x, color.y, color.z);
	glUniform1f(glGetUniformLocation(shaderID, "material.opacity"), 0.4f);

	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);
	glBindVertexArray(0);
}

void BoundingBox::Update(GLfloat deltaTime)
{
	GameObject::Update(deltaTime);
	//Render(shaderID);

	if (node->GetParent() == NULL)
	{
		printf("Set a GameObjectNode for the BoundingBox\n");
	}
}

void BoundingBox::SetGameObjectNode(Node* gameObjectNode)
{
	gameObjectNode->AddChild(this->node);
	parentGameObjectNode = gameObjectNode;
}

glm::vec3 BoundingBox::GetBoundingBoxSize()
{
	glm::vec3 boundingBoxSize;

	if (this->node->m_vSize == this->parentGameObjectNode->m_vSize)
	{
		boundingBoxSize = this->node->m_vSize;
	}
	else
	{
		if (glm::length(node->m_vSize) - glm::length(parentGameObjectNode->m_vSize) > 0)
		{
			boundingBoxSize = this->node->m_vSize;
		}

		if (glm::length(node->m_vSize) - glm::length(parentGameObjectNode->m_vSize) < 0)
		{
			boundingBoxSize = this->parentGameObjectNode->m_vSize;
		}
	}
	return boundingBoxSize;
}