#pragma once
#include "afx.h"
class NewtonianPhysics 
{
private:
	void LinearMechanics(GLfloat deltaTime);
	void Gravity(GLfloat deltaTime);
public:
	NewtonianPhysics(void);
	NewtonianPhysics(GLfloat mass);
	~NewtonianPhysics(void);

	GLfloat		m_fMass;

	glm::vec3	m_vPosition;
	glm::vec3	m_vSize;

	glm::vec3	m_vEulerAngles;
	glm::quat	m_vRotation;
	
	glm::vec3	m_vVelocity;
	glm::vec3	m_vAcceleration;

	glm::vec3	m_vForce;
	glm::vec3	m_vFriction;
	GLfloat		m_fMaxSpeed;
	GLfloat		m_fMaxForce; 

	GLboolean gravity;

	void Update(GLfloat deltaTime);
	void ApplyForce(glm::vec3 force);
	void SetFriction(glm::vec3 frictionCoefficient);
	glm::vec3 GetCurrentForce();
	void ClearForce();
	void ClearVelocity();

};

