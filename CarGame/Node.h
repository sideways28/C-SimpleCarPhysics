#pragma once
#include "afx.h"

struct Axis
{
	glm::vec3 right;
	glm::vec3 up;
	glm::vec3 forward;
};

class Node : public NewtonianPhysics
{
private:
	char* nodeName;
	Node* m_oParent;

	glm::vec3 m_vGlobalPos;

	float x;//For Rotations
	float y;
	float z;
	float w;

public:
	Node();
	Node(GameObject* go);
	~Node();

	Axis localAxis;
	//Axis globalAxis;

	glm::mat4 m_mLocalTransform;
	glm::mat4 m_mGlobalTransform;

	GLuint shaderID;

	std::list<Node*> m_nChildren;
	GameObject* m_oGameObject;

	glm::vec3 GetGlobalPos();

	void SetNodeName(char* nodeName);
	char* GetNodeName();
	void Attach(GameObject* go);
	void SetParent(Node* node);
	Node* GetParent();
	void AddChild(Node* child);
	void RemoveChild(Node* child);

	void Update(GLfloat deltaTime);

	void PrintVector3(const glm::vec3& vec);
	void PrintMat4(const glm::mat4& mat);
};

