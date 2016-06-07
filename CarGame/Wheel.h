#pragma once
#include "afx.h"

class Wheel : public GameObject
{
public:
	Wheel();
	~Wheel();

	Node* node;

private :	
	void Initialize();
	void Render(GLuint shaderID);
	void Update(GLfloat deltaTime);
};

