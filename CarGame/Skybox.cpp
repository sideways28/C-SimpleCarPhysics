#include "Skybox.h"


Skybox::Skybox()
	: vertexBuffer(0)
{
	memset(&m_vPosition, 0, sizeof(glm::vec3));
	memset(&m_vRotation, 0, sizeof(glm::vec3));

	m_vSize = glm::vec3(1);
}


Skybox::~Skybox()
{
	
}

void Skybox::Initialize()
{
	GLfloat vertices[] =
	{
		-0.5f,-0.5f, 0.5f,			0.0f, 1.0f, 0.0f,		0.0f, 0.0f,//Front
		-0.5f, 0.5f, 0.5f,			0.0f, 1.0f, 0.0f,		0.0f, 1.0f,
		 0.5f, 0.5f, 0.5f,			0.0f, 1.0f, 0.0f,		1.0f, 1.0f,
		 0.5f, 0.5f, 0.5f,			0.0f, 1.0f, 0.0f,		1.0f, 1.0f,
		 0.5f,-0.5f, 0.5f,			0.0f, 1.0f, 0.0f,		1.0f, 0.0f,
		-0.5f,-0.5f, 0.5f,			0.0f, 1.0f, 0.0f,		0.0f, 0.0f,
									
		 0.5f,-0.5f,-0.5f,			0.0f, 1.0f, 0.0f,		0.0f, 0.0f,//Back
		 0.5f, 0.5f,-0.5f,			0.0f, 1.0f, 0.0f,		0.0f, 1.0f,
		-0.5f, 0.5f,-0.5f,			0.0f, 1.0f, 0.0f,		1.0f, 1.0f,								   
		-0.5f, 0.5f,-0.5f,			0.0f, 1.0f, 0.0f,		1.0f, 1.0f,
		-0.5f,-0.5f,-0.5f,			0.0f, 1.0f, 0.0f,		1.0f, 0.0f,
		 0.5f,-0.5f,-0.5f,			0.0f, 1.0f, 0.0f,		0.0f, 0.0f,
									
		 0.5f,-0.5f, 0.5f,			0.0f, 1.0f, 0.0f,		0.0f, 0.0f,//Right
		 0.5f, 0.5f, 0.5f,			0.0f, 1.0f, 0.0f,		0.0f, 1.0f,
		 0.5f, 0.5f,-0.5f,			0.0f, 1.0f, 0.0f,		1.0f, 1.0f,				   	   		    
		 0.5f, 0.5f,-0.5f,			0.0f, 1.0f, 0.0f,		1.0f, 1.0f,
		 0.5f,-0.5f,-0.5f,			0.0f, 1.0f, 0.0f,		1.0f, 0.0f,
		 0.5f,-0.5f, 0.5f,			0.0f, 1.0f, 0.0f,		0.0f, 0.0f,
									
		-0.5f,-0.5f,-0.5f,			0.0f, 1.0f, 0.0f,		0.0f, 0.0f,//Left
		-0.5f, 0.5f,-0.5f,			0.0f, 1.0f, 0.0f,		0.0f, 1.0f,
		-0.5f, 0.5f, 0.5f,			0.0f, 1.0f, 0.0f,		1.0f, 1.0f,						    
		-0.5f, 0.5f, 0.5f,			0.0f, 1.0f, 0.0f,		1.0f, 1.0f,
		-0.5f,-0.5f, 0.5f,			0.0f, 1.0f, 0.0f,		1.0f, 0.0f,
		-0.5f,-0.5f,-0.5f,			0.0f, 1.0f, 0.0f,		0.0f, 0.0f,	
										
		 0.5f, 0.5f,-0.5f,			0.0f, 1.0f, 0.0f,		0.0f, 0.0f,//Up
		 0.5f, 0.5f, 0.5f,			0.0f, 1.0f, 0.0f,		0.0f, 1.0f,
		-0.5f, 0.5f, 0.5f,			0.0f, 1.0f, 0.0f,		1.0f, 1.0f, 			   	   
		-0.5f, 0.5f, 0.5f,			0.0f, 1.0f, 0.0f,		1.0f, 1.0f,
		-0.5f, 0.5f,-0.5f,			0.0f, 1.0f, 0.0f,		1.0f, 0.0f,
		 0.5f, 0.5f,-0.5f,			0.0f, 1.0f, 0.0f,		0.0f, 0.0f,
							
		 0.5f,-0.5f, 0.5f,			0.0f, 1.0f, 0.0f,		0.0f, 0.0f,//Down
		 0.5f,-0.5f,-0.5f,			0.0f, 1.0f, 0.0f,		0.0f, 1.0f,
		-0.5f,-0.5f,-0.5f,			0.0f, 1.0f, 0.0f,		1.0f, 1.0f, 			   	   
		-0.5f,-0.5f,-0.5f,			0.0f, 1.0f, 0.0f,		1.0f, 1.0f,
		-0.5f,-0.5f, 0.5f,			0.0f, 1.0f, 0.0f,		1.0f, 0.0f,
		 0.5f,-0.5f, 0.5f,			0.0f, 1.0f, 0.0f,		0.0f, 0.0f,
	};

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	m_vSize = glm::vec3(500);
}

void Skybox::Render(GLuint shaderID)
{
	glm::mat4 modelMatrix = glm::scale(glm::mat4(1), m_vSize);
	glUniformMatrix4fv(glGetUniformLocation(shaderID, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	glEnableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 32, (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 32, (void*)12);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 32, (void*)24);

	TextureManager::GetInstance()->SetActive("Front.png");
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	TextureManager::GetInstance()->ClearTexture();

	TextureManager::GetInstance()->SetActive("Back.png");
	glDrawArrays(GL_TRIANGLES, 6, 6);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	TextureManager::GetInstance()->ClearTexture();


	TextureManager::GetInstance()->SetActive("Left.png");
	glDrawArrays(GL_TRIANGLES, 12, 6);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	TextureManager::GetInstance()->ClearTexture();

	TextureManager::GetInstance()->SetActive("Right.png");
	glDrawArrays(GL_TRIANGLES, 18, 6);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	TextureManager::GetInstance()->ClearTexture();

	TextureManager::GetInstance()->SetActive("Top.png");
	glDrawArrays(GL_TRIANGLES, 24, 6);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	TextureManager::GetInstance()->ClearTexture();

	
	TextureManager::GetInstance()->SetActive("Bottom.png");
	glDrawArrays(GL_TRIANGLES, 30, 6);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	TextureManager::GetInstance()->ClearTexture();

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void Skybox::Update(GLfloat deltaTime)
{
	
}
