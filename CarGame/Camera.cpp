#include "Camera.h"

Camera::Camera(void)
	:onGround(false),
	goingBack(false),
	m_fPanSpeed(0.1f)
{
	memset(&m_vRight, 0, sizeof(glm::vec3));
	memset(&m_vUp, 0, sizeof(glm::vec3));
	memset(&m_vForward, 0, sizeof(glm::vec3));

	viewMatrix = glm::mat4(1);

	m_vPosition = glm::vec3(0.0f, 10.0f, -20.0f);
	m_vRotation = glm::vec3(-30.0f, 180.0f, 0.0f);

	m_fMoveSpeed = 10.0f;
	m_fRotateSpeed = 10.0f;

	m_vCamOriginalPos = m_vPosition;
	m_vCamOriginalRot = m_vRotation;

	this->node = new Node();
}

Camera::~Camera()
{

}

void Camera::SetMoveSpeed(GLfloat _moveSpeed)
{
	m_fMoveSpeed = _moveSpeed;
}

void Camera::SetRotationSpeed(GLfloat _rotateSpeed)
{
	m_fRotateSpeed = _rotateSpeed;
}

void Camera::Update(GLfloat deltaTime)
{
	Move(deltaTime);

	m_vRight = glm::vec3(viewMatrix[0][0], viewMatrix[1][0], viewMatrix[2][0]);
	m_vRight = glm::normalize(m_vRight);
	m_vUp = glm::vec3(viewMatrix[0][1], viewMatrix[1][1], viewMatrix[2][1]);
	m_vUp = glm::normalize(m_vUp);
	m_vForward = glm::vec3(viewMatrix[0][2], viewMatrix[1][2], viewMatrix[2][2]);
	m_vForward = glm::normalize(m_vForward);
}

glm::mat4 Camera::GetMatrix()
{
	viewMatrix = glm::mat4(1);

	if (this->node->GetParent())
	{
		//this->m_vPosition += glm::vec3(targetNode->m_vPosition + targetOffset - this->m_vPosition) * m_fPanSpeed;

		//Set camera's position to it's nodes position which which has a parent(target) to follow
		this->m_vPosition = glm::vec3(this->node->m_mGlobalTransform[3][0], this->node->m_mGlobalTransform[3][1], this->node->m_mGlobalTransform[3][2]);
		
		viewMatrix = glm::lookAt(m_vPosition, this->node->GetParent()->m_vPosition, glm::vec3(0, 1, 0));
	}
	else
	{
		viewMatrix = glm::rotate(viewMatrix, -glm::radians(m_vRotation.x), glm::vec3(1, 0, 0));
		viewMatrix = glm::rotate(viewMatrix, -glm::radians(m_vRotation.y), glm::vec3(0, 1, 0));
		viewMatrix = glm::rotate(viewMatrix, -glm::radians(m_vRotation.z), glm::vec3(0, 0, 1));
		viewMatrix = glm::translate(viewMatrix, -m_vPosition);
	}

	return viewMatrix;
}

void Camera::Reset()
{
	m_vPosition = m_vCamOriginalPos;
	m_vRotation = m_vCamOriginalRot;
}

void Camera::Move(GLfloat deltaTime)
{
	if (this->node->GetParent() == NULL)
	{
		if (InputManager::GetInstance()->vertical > 0)
		{
			m_vPosition -= m_vForward * m_fMoveSpeed * deltaTime;
			goingBack = false;
		}

		if (InputManager::GetInstance()->vertical < 0)
		{
			m_vPosition += m_vForward * m_fMoveSpeed * deltaTime;
			goingBack = true;
		}

		if (InputManager::GetInstance()->horizontal > 0)
		{
			m_vPosition += m_vRight * m_fMoveSpeed * deltaTime;
		}

		if (InputManager::GetInstance()->horizontal < 0)
		{
			m_vPosition -= m_vRight * m_fMoveSpeed * deltaTime;
		}
	}
}

void Camera::Yaw(GLfloat yawSpeed)
{
	if (this->node->GetParent() == NULL)
		m_vRotation.y -= m_fRotateSpeed * yawSpeed;
}

void Camera::Pitch(GLfloat pitchSpeed)
{
	if (this->node->GetParent() == NULL)
		m_vRotation.x -= m_fRotateSpeed * pitchSpeed;
}

void Camera::Roll(GLfloat rollSpeed)
{
	if (this->node->GetParent() == NULL)
		m_vRotation.z -= m_fRotateSpeed * rollSpeed;
}


