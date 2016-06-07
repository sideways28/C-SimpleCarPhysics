#pragma once
#include "Shader.h"
#include "ShaderProgram.h"

class ShaderManager
{
private:
	ShaderManager(void);
	static ShaderManager* m_pInstance;
	std::map<std::string, ShaderProgram*> mShaders;

public:
	~ShaderManager(void);
	static ShaderManager* GetInstance();

	void Initialize();
	void BuildShaderDictionary();
	void LoadShadersFromDictionary();
	void UseShader(std::string name);
	GLuint ProgramId(std::string name);
	void ShaderManager::DeleteShader(std::string name);
};

