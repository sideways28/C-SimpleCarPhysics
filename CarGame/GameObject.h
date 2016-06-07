#pragma once
#include "Model.h"

struct BoundingBox
{
	float left;
	float right;
	float up;
	float down;
	float front;
	float back;
};

class GameObject 
{
public:
	GameObject();
	~GameObject();

	bool isInitialized;
	GLuint shaderID;

protected:
	Model* m_oModel;
	void LoadModel(char* path, char* modelName);

public:	
	virtual void Initialize();
	virtual void Render(GLuint shaderID);
	virtual void Update(GLfloat deltaTime);

	BoundingBox boundingBox;
};

