#pragma once
#include "afx.h"

class Camera
{
private:
	glm::vec3 m_vCamOriginalPos;
	glm::vec3 m_vCamOriginalRot;

public:
	glm::vec3 m_vPosition;
	GLfloat m_fMoveSpeed;
	glm::vec3 m_vRotation;
	GLfloat m_fRotateSpeed;

	glm::mat4 viewMatrix;

	Node* node;

	float m_fPanSpeed;

public:
	glm::vec3 m_vRight;
	glm::vec3 m_vUp;
	glm::vec3 m_vForward;

public:
	Camera(void);
	~Camera(void);

	GLboolean goingBack;
	GLboolean onGround;

	void SetMoveSpeed(GLfloat _moveSpeed);
	void SetRotationSpeed(GLfloat _rotateSpeed);

	void Update(GLfloat deltaTime);
	glm::mat4 GetMatrix();

	void Reset();

	void Move(GLfloat deltaTime);

	void Yaw(GLfloat yawSpeed);
	void Pitch(GLfloat pitchSpeed);
	void Roll(GLfloat rollSpeed);
};