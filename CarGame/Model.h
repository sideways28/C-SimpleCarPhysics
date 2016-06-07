#pragma once
#include "Mesh.h"
#include "ShaderManager.h"

class Model
{
private:
	vector<Mesh> meshes;
	string directory;
	vector<Texture> textures_loaded;

	void LoadModel(char* directory, char* modelName);
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);

	Material material;
public:
	Model(char* directory, char* modelName);//Location & modelName
	~Model();
	void Render(GLuint shaderID);
	GLint TextureFromFile(const char* path, string directory);
};

