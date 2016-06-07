#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <GL\glew.h>
#include <iostream>
#include <vector>
#include <GLM\glm.hpp>
#include <GLM\gtc\matrix_transform.hpp>
#include <GLM\gtc\type_ptr.hpp>
#include "TextureManager.h"
#include "afx.h"

class Terrain : public GameObject
{
private:
	GLuint vertexArray;
	GLuint vertexBuffer;
	GLuint uvBuffer;
	GLuint normalBuffer;
	GLuint indexBuffer;

	int width;//Width of Terrain Image or HeightMapImage when loaded
	int height;//Height of Terrain Image or HeightMapImage when loaded

	//GLuint terrainTex;
	char* terrainTexture;//Terrain texture
	unsigned char** m_pHeight;//Pointer to store all the height data

	std::vector<glm::vec3> m_nVertices;
	std::vector<glm::vec3> m_nNormals;
	std::vector<glm::vec2> m_nTexCoords;
	std::vector<GLuint> m_nIndices;
	glm::vec3 m_vPosition;

	float Height(GLubyte* pHeightMap, int X, int Y);

	std::vector<glm::vec2>m_nHeightCoords;
	std::vector<float>m_nHeightValues;
	float Terrain::HeightAtCoord(float gridX, float gridZ);
	float BarryCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos);

public:
	Terrain(char* terrainTexture, char* heightMapRawFile, int _width, int _height);//When loading with heightdata
	~Terrain();

	Node* node;

	float GetHeightFromCoord(int playerX, int playerZ);

private:
	void Initialize();
	void Render(GLuint shaderID);
	void Release();
	void Update(GLfloat deltaTime);
};

