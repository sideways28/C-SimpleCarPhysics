#pragma once
#include "afx.h"

class Skybox 
{
private:
	glm::vec3 m_vPosition;
	glm::vec3 m_vRotation;
	glm::vec3 m_vSize;

	GLuint vertexBuffer;

public:
	Skybox();
	~Skybox();

	void Initialize();
	void Render(GLuint shaderID);
	void Update(GLfloat deltaTime);
};

