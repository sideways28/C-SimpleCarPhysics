#include "Node.h"

Node::Node() : 
m_oGameObject(NULL),
m_oParent(NULL),
nodeName(NULL)
{
	memset(&m_vPosition, 0, sizeof(glm::vec3));
	memset(&m_vRotation, 0, sizeof(glm::vec3));
	m_vSize = glm::vec3(1.0f);
}

Node::Node(GameObject* go)
	:m_oGameObject(NULL),
	m_oParent(NULL),
	nodeName(NULL)
{
	Attach(go);
}


Node::~Node()
{
	m_nChildren.clear();
}

void Node::AddChild(Node* child)
{
	m_nChildren.push_back(child);
	child->SetParent(this);
}

void Node::SetParent(Node* parentNode)
{
	this->m_oParent = parentNode;
}

Node* Node::GetParent()
{
	return m_oParent;
}

void Node::RemoveChild(Node* childNode)
{
	m_nChildren.remove(childNode);
}

void Node::Attach(GameObject* go)
{
	this->m_oGameObject = go;
}

void Node::SetNodeName(char* nodeName)
{
	this->nodeName = nodeName;
}

char* Node::GetNodeName()
{
	return this->nodeName;
}

void Node::Update(GLfloat deltaTime)
{
	NewtonianPhysics::Update(deltaTime);

	glm::mat4 translationMatrix = glm::translate(glm::mat4(1), m_vPosition);

	glm::mat4 rotationMatrix = 
		glm::rotate(glm::mat4(1), m_vRotation.y, glm::vec3(0, 1, 0)) *
		glm::rotate(glm::mat4(1), m_vRotation.z, glm::vec3(0, 0, 1)) *
		glm::rotate(glm::mat4(1), m_vRotation.x, glm::vec3(1, 0, 0));

	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1), m_vSize);

	m_mLocalTransform = translationMatrix * rotationMatrix * scaleMatrix;

	if (m_oParent)
	{
		m_mGlobalTransform = m_oParent->m_mGlobalTransform * m_mLocalTransform;
	}
	else
	{
		m_mGlobalTransform = m_mLocalTransform;
	}

	if (nodeName)
	{
		if (shaderID)
		{
			glUniformMatrix4fv(glGetUniformLocation(shaderID, "model"), 1, GL_FALSE, &m_mGlobalTransform[0][0]);
		}
		else
		{
			if (nodeName != "Scene RootNode")
			{
				printf("ShaderID of %s Node not set\n", nodeName);
			}
		}
	}

	if (m_oGameObject)
	{
		m_oGameObject->Render(shaderID);
		m_oGameObject->Update(deltaTime);
	}

	for (auto it = m_nChildren.begin(); it != m_nChildren.end(); it++)
	{
		(*it)->Update(deltaTime);
	}

	//Local Axis
	localAxis.right = glm::normalize(glm::vec3(-m_mLocalTransform[0][0], m_mLocalTransform[0][1], m_mLocalTransform[0][2]));
	localAxis.up = glm::normalize(glm::vec3(m_mLocalTransform[1][0], m_mLocalTransform[1][1], m_mLocalTransform[1][2]));
	localAxis.forward = glm::normalize(glm::vec3(m_mLocalTransform[2][0], m_mLocalTransform[2][1], m_mLocalTransform[2][2]));

	////Global Axis
	//globalAxis.right = glm::vec3(m_mGlobalTransform[0][0], m_mGlobalTransform[0][1], m_mGlobalTransform[0][2]);
	//globalAxis.up = glm::vec3(m_mGlobalTransform[1][0], m_mGlobalTransform[1][1], m_mGlobalTransform[1][2]);
	//globalAxis.forward = glm::vec3(m_mGlobalTransform[2][0], m_mGlobalTransform[2][1], m_mGlobalTransform[2][2]);

	//globalAxis.right = glm::normalize(globalAxis.right);
	//globalAxis.up = glm::normalize(globalAxis.up);
	//globalAxis.forward = glm::normalize(globalAxis.forward);
}

glm::vec3 Node::GetGlobalPos()
{
	m_vGlobalPos = glm::vec3(m_mGlobalTransform[3][0], m_mGlobalTransform[3][1], m_mGlobalTransform[3][2]);
	return m_vGlobalPos;
}

void Node::PrintVector3(const glm::vec3& vec)
{
	printf("%f,%f,%f\n", vec.x, vec.y, vec.z);
}

void Node::PrintMat4(const glm::mat4& mat)
{
	printf("\n%f,%f,%f,%f\n", mat[0][0], mat[0][1], mat[0][2], mat[0][3]);
	printf("%f,%f,%f,%f\n", mat[1][0], mat[1][1], mat[1][2], mat[1][3]);
	printf("%f,%f,%f,%f\n", mat[2][0], mat[2][1], mat[2][2], mat[2][3]);
	printf("%f,%f,%f,%f\n", mat[3][0], mat[3][1], mat[3][2], mat[3][3]);
}