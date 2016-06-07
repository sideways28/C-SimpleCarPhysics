#pragma once
#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <memory.h>

#include <GL\glew.h>

#include <SOIL\SOIL.h>

#include <GLM\glm.hpp>
#include <GLM\gtc\matrix_transform.hpp>

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

using namespace std;

struct Material
{
	aiString name;
	aiColor3D ambient;
	aiColor3D diffuse;
	aiColor3D specular;
	float opacity;
	float shininess;
};

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture
{
	GLuint id;
	std::string type;
	aiString path;
};

class Mesh
{
private:
	GLuint VAO, VBO, EBO;
	void SetupMesh();

	Material meshMat;

public:
	~Mesh();

	int texCount;

	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;

	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures, Material material);
	void Draw(GLuint shaderID);
};

