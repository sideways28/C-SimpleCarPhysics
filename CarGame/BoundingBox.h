#pragma once
#include "GameObject.h"
#include "Node.h"

class BoundingBox : public GameObject
{
private:
	GLuint VAO;//BoundingBox vao
	GLuint VBO;
	GLuint EBO;
	glm::vec3 m_vGlobalSize;

	float left;
	float right;
	float up;
	float down;
	float front;
	float back;

public:
	BoundingBox();
	~BoundingBox();

	glm::vec3 color;
	bool fall;

	Node* node;
	Node* parentGameObjectNode;
	void SetGameObjectNode(Node* gameObjectNode);
	glm::vec3 GetBoundingBoxSize();

	void Initialize();
	void Render(GLuint shaderID);
	void Update(GLfloat deltaTime);
};

