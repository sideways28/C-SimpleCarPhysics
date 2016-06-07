#pragma once
#include "afx.h"

class Car : public GameObject
{
public:
	Car();
	~Car();

	Node* node;
private:
	void Initialize();
	void Render(GLuint shaderID);
	void Update(GLfloat deltaTime);
};

