#include "Terrain.h"

Terrain::Terrain(char* _terrainTexture, char* heightMapRawFile, int _width, int _height)
	:vertexBuffer(0),
	indexBuffer(0)
{
	node = new Node(this);

	terrainTexture = _terrainTexture;
	memset(&m_vPosition, 0, sizeof(glm::vec3));
	width = _width;
	height = _height;

	m_pHeight = (unsigned char**)malloc(width*height);

	char* rootDir = "Resources\\Textures\\";

	char* rawFileFullPath = NULL;
	rawFileFullPath = (char*)malloc((strlen(rootDir) + strlen(heightMapRawFile) + 1) * sizeof(char));
	memset(rawFileFullPath, 0, (strlen(rootDir) + strlen(heightMapRawFile) + 1) * sizeof(char));
	strcat_s(rawFileFullPath, (strlen(rootDir) + strlen(heightMapRawFile) + 1) * sizeof(char), rootDir);
	strcat_s(rawFileFullPath, (strlen(rootDir) + strlen(heightMapRawFile) + 1) * sizeof(char), heightMapRawFile);

	//Loading raw file
	FILE* pFile = NULL;
	pFile = fopen(rawFileFullPath, "rb");

	if (pFile == NULL)
	{
		printf("Unable to Load HeightMap\n");
		return;
	}

	//putting the data of pFile in heightMap
	fread(m_pHeight, 1, width*height, pFile);

	int result = ferror(pFile);

	if (result)
	{
		printf("Failed to get Data from HeightMap\n");
	}

	fclose(pFile);
}

Terrain::~Terrain()
{
	Release();
}

float Terrain::Height(GLubyte* pHeightMap, int _x, int _y)
{
	int x = _x % width;
	int y = _y % height;

	if (pHeightMap)
		return pHeightMap[x + (y * width)];
	else
		return 0;
}

float Terrain::BarryCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos)
{
	float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.x - p3.x);
	float a = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
	float b = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
	float c = 1.0f - a - b;

	return (a * p1.y) + (b * p2.y) + (c * p3.y);
}

float Terrain::HeightAtCoord(float gridX, float gridZ)
{
	for (auto it = m_nHeightCoords.begin(); it != m_nHeightCoords.end(); it++)
	{
		static int index = 0;

		if (m_nHeightCoords.at(index) == glm::vec2(gridX, gridZ))
		{
			//printf("Index : %d\n", index);
			return m_nHeightValues.at(index);
		}
		else
		{
			index++;
		}

		if (index == m_nHeightCoords.size())
		{
			printf("The value isn't in the vector\n");
			return 0;
		}
	}

	return 0;
}

float Terrain::GetHeightFromCoord(int coordX, int coordZ)
{
	int terrainX = coordX + 128;
	int terrainZ = coordZ + 128;

	int terrainWidth = 256;
	int numberofGridX = 255;
	int gridSizeX = terrainWidth / numberofGridX;

	int terrainHeight = 256;
	int numberofGridZ = 255;
	int gridSizeZ = terrainHeight / numberofGridZ;

	int currentGridX = glm::floor(terrainX / gridSizeX);
	int currentGridZ = glm::floor(terrainZ / gridSizeZ);

	if (currentGridX >= numberofGridX || currentGridZ >= numberofGridZ || currentGridX < 0 || currentGridZ < 0)
	{
		return 0;
	}

	float xCoord = (terrainX % gridSizeX) / gridSizeX;
	float zCoord = (terrainZ % gridSizeZ) / gridSizeZ;

	float res = 0;
	
	if (xCoord < (1 - zCoord))
	{
		res = BarryCentric(glm::vec3(0, HeightAtCoord(currentGridX, currentGridZ), 0), glm::vec3(1, HeightAtCoord(currentGridX + 1, currentGridZ), 0), glm::vec3(0, HeightAtCoord(currentGridX, currentGridZ + 1), 1), glm::vec2(xCoord, zCoord));
	}
	else
	{
		res = BarryCentric(glm::vec3(1, HeightAtCoord(currentGridX + 1, currentGridZ), 0), glm::vec3(1, HeightAtCoord(currentGridX + 1, currentGridZ + 1), 0), glm::vec3(0, HeightAtCoord(currentGridX, currentGridZ + 1), 1), glm::vec2(xCoord, zCoord));
	}

	return res;
}

void Terrain::Initialize()
{
	boundingBox.left = -128;
	boundingBox.right = 128;
	boundingBox.up = 0.0005f;
	boundingBox.down = -0.0005f;
	boundingBox.front = -128;
	boundingBox.back = 128;

	GameObject::Initialize();

	glGenVertexArrays(1, &this->vertexArray);
	glBindVertexArray(this->vertexArray);

	//Calculating UV Offset 
	glm::vec2 uvOffset = glm::vec2(1.0f / (GLfloat)width, 1.0f / (GLfloat)height);

	//Generating vertices
	for (int z = 0; z <= height; z++)
	{
		for (int x = 0; x <= width; x++)
		{
			//Generating height data
			float height = 0;//(float)Height((GLubyte*)m_pHeight, x, z) / 10.0f;

			//Setting HeightCoords to fetch height from it later
			m_nHeightCoords.push_back(glm::vec2(x, z));
			//Pushing Heights to compare it with coords later 
			m_nHeightValues.push_back(height);

			//Generating vertices
			m_nVertices.push_back(glm::vec3(x, height, z));

			//Generating Normals
			m_nNormals.push_back(glm::normalize(glm::vec3(0, 1, 0)));

			//Generating TexCoords(Full Terrain Mapping)
			m_nTexCoords.push_back(glm::vec2(x * uvOffset.x, z * uvOffset.y));
		}
	}

	//Generating Indices
	static int loopIncrement = 0;
	for (int z = 0; z < height; z++)
	{
		for (int x = 0; x < width; x++)
		{
			int index = x + (z * width) + loopIncrement;

			m_nIndices.push_back(index);
			m_nIndices.push_back(index + width + 1);
			m_nIndices.push_back(index + 1);
			m_nIndices.push_back(index + 1);
			m_nIndices.push_back(index + width + 1);
			m_nIndices.push_back(index + width + 2);
		}
		//After end of every x++ loop Add a +1 to loopIncrement 
		loopIncrement++;
	}

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_nVertices.size() * sizeof(glm::vec3), &m_nVertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glGenBuffers(1, &normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_nNormals.size() * sizeof(glm::vec3), &m_nNormals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_nTexCoords.size() * sizeof(glm::vec2), &m_nTexCoords[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_nIndices.size() * sizeof(GLuint), &m_nIndices[0], GL_STATIC_DRAW_ARB);

	glBindVertexArray(0);
}

void Terrain::Render(GLuint shaderID)
{
	GameObject::Render(shaderID);

	TextureManager::GetInstance()->SetActive(terrainTexture);
	glUniform1i(glGetUniformLocation(shaderID, "material.texCount"), 1);
	glUniform1f(glGetUniformLocation(shaderID, "material.opacity"), 1);

	glm::mat4 modelMatrix = glm::translate(glm::mat4(1), glm::vec3(-width / 2, 0, -height / 2));
	glUniformMatrix4fv(glGetUniformLocation(shaderID, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));

	glBindVertexArray(this->vertexArray);
	glDrawElements(GL_TRIANGLES, m_nIndices.size(), GL_UNSIGNED_INT, (void*)0);
	glBindVertexArray(0);

	TextureManager::GetInstance()->ClearTexture();
}

void Terrain::Update(GLfloat deltaTime)
{
	GameObject::Update(deltaTime);
}

void Terrain::Release()
{
	delete[] m_pHeight;
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
}