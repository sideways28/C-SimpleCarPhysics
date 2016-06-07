#include "afx.h"


NewtonianPhysics::NewtonianPhysics(void)
	:m_fMass(1)
	,m_fMaxSpeed(100)
	,m_fMaxForce(100)
	, gravity(false)
{
	memset(&m_vPosition, 0, sizeof(glm::vec3));
	memset(&m_vRotation, 0, sizeof(glm::vec3));
	m_vSize = glm::vec3(1);

	memset(&m_vVelocity, 0, sizeof(glm::vec3));
	memset(&m_vAcceleration, 0, sizeof(glm::vec3));
	memset(&m_vForce, 0, sizeof(glm::vec3));
	memset(&m_vFriction, 0, sizeof(glm::vec3));
}

NewtonianPhysics::NewtonianPhysics(GLfloat mass)
	:m_fMass(mass)
	,m_fMaxSpeed(100)
	,m_fMaxForce(100)
{
	memset(&m_vPosition, 0, sizeof(glm::vec3));
	memset(&m_vSize, 0, sizeof(glm::vec3));
	memset(&m_vVelocity, 0, sizeof(glm::vec3));
	memset(&m_vAcceleration, 0, sizeof(glm::vec3));
	memset(&m_vForce, 0, sizeof(glm::vec3));
	memset(&m_vFriction, 0, sizeof(glm::vec3));
}

NewtonianPhysics::~NewtonianPhysics(void)
{

}

void NewtonianPhysics::Update(GLfloat deltaTime)
{
	LinearMechanics(deltaTime);

	if (gravity)
	{
		//Gravity(deltaTime);
		//this->m_vPosition.y -= 9.8f * deltaTime;
	}
}

void NewtonianPhysics::ApplyForce(glm::vec3 force)
{
	m_vForce+=force;
}

void NewtonianPhysics::LinearMechanics(GLfloat deltaTime)
{
	float massInverse = 1 / m_fMass;
	//Force = mass*acceleration
	m_vAcceleration = m_vForce * massInverse;

	//Velocity = initial Velocity*Acceleration
	m_vVelocity = m_vVelocity + m_vAcceleration * deltaTime;

	//Displacement = Velocity*time
	m_vPosition += m_vVelocity * deltaTime;


	if (glm::length(m_vForce) >= m_fMaxForce)//Limit Force
	{
		m_vForce = glm::normalize(m_vForce);
		m_vForce = m_vForce * m_fMaxForce;
	}

	if (glm::length(m_vVelocity) > m_fMaxSpeed)//Limit Velocity
	{
		m_vVelocity = glm::normalize(m_vVelocity);
		m_vVelocity = m_vVelocity * m_fMaxSpeed;
	}

	//retartation due to friction
	m_vForce = m_vForce - m_vForce*m_vFriction;
	m_vVelocity = m_vVelocity - m_vVelocity*m_vFriction;
}

void NewtonianPhysics::Gravity(GLfloat deltaTime)
{
	glm::vec3 accDueToGravity = glm::vec3(0, -1, 0) * 9.8f;
	glm::vec3 velDueToGravity = velDueToGravity + accDueToGravity * deltaTime;
	m_vPosition += velDueToGravity * deltaTime;
}

glm::vec3 NewtonianPhysics::GetCurrentForce()
{
	return m_vForce;
}

void NewtonianPhysics::SetFriction(glm::vec3 friction)
{
	m_vFriction = friction;
}

void NewtonianPhysics::ClearForce()
{
	memset(&m_vForce, 0, sizeof(glm::vec3));
}

void NewtonianPhysics::ClearVelocity()
{
	memset(&m_vVelocity, 0, sizeof(glm::vec3));
}

