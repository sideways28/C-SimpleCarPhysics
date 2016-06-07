#pragma once
#include "afx.h"

class Crate : public GameObject
{
public:
	Crate();
	~Crate();

	Node* node;

private:
	void Initialize();
	void Render(GLuint shaderID);
	void Update(GLfloat deltaTime);
};

