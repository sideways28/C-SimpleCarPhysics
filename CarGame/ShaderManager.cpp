#include "ShaderManager.h"


ShaderManager::ShaderManager(void)
{
}


ShaderManager::~ShaderManager(void)
{

}

ShaderManager* ShaderManager::m_pInstance = NULL;

ShaderManager* ShaderManager::GetInstance()
{
	if(!m_pInstance)
	{
		m_pInstance = new ShaderManager();
	}
	return m_pInstance;
}
void ShaderManager::Initialize()
{
	BuildShaderDictionary();
	LoadShadersFromDictionary();
}

void ShaderManager::BuildShaderDictionary()
{
	char* rootDirectory = "Resources\\Shaders\\";
	char* extension = "*";

	WIN32_FIND_DATAA wfd = {0};
	char* fullPath = NULL;
	fullPath = (char*) malloc((strlen(rootDirectory) + strlen(extension) + 1) * sizeof(char));
	memset(fullPath, 0, (strlen(rootDirectory) + strlen(extension) + 1) * sizeof(char));
	strcat_s(fullPath, (strlen(rootDirectory) + strlen(extension) + 1) * sizeof(char), rootDirectory);
	strcat_s(fullPath, (strlen(rootDirectory) + strlen(extension) + 1) * sizeof(char), extension);

	HANDLE handle = FindFirstFileA(fullPath, &wfd);

	delete(fullPath);

	while(handle != INVALID_HANDLE_VALUE)
	{
		if(FindNextFileA(handle, &wfd) == FALSE)
			break;

		if(strcmp(wfd.cFileName, "..") == 0 || strcmp(wfd.cFileName, ".") == 0)
			continue;
		
		std::string filename(wfd.cFileName);
		filename = filename.substr(0, filename.length() - 5);//5 is Length of (.vert or .frag) which should be removed from the string filename
		
		if(mShaders.find(filename) != mShaders.end()){
			continue;
		} else {
			mShaders[filename]  = NULL;
		}
	}
}


void ShaderManager::LoadShadersFromDictionary()
{
	//std::map<std::string, ShaderProgram*>::iterator it = mShaders.begin();

	//while(it != mShaders.end())
	for (auto it = mShaders.begin(); it != mShaders.end(); it++)
	{
		ShaderProgram* sp = new ShaderProgram();
		char* rootDirectory = "Resources\\Shaders\\";
		char* extension = ".vert";
		char* fullPath = NULL;
		fullPath = (char*) malloc((strlen(rootDirectory) + it->first.length() + strlen(extension) + 1) * sizeof(char));
		memset(fullPath, 0, (strlen(rootDirectory) + it->first.length()  + strlen(extension) + 1) * sizeof(char));
		strcat_s(fullPath, (strlen(rootDirectory) + it->first.length() + strlen(extension) + 1) * sizeof(char), rootDirectory);
		strcat_s(fullPath, (strlen(rootDirectory) + it->first.length() + strlen(extension) + 1) * sizeof(char), it->first.c_str());
		strcat_s(fullPath, (strlen(rootDirectory) + it->first.length() + strlen(extension) + 1) * sizeof(char), extension);

		sp->vs = new Shader(GL_VERTEX_SHADER, fullPath);

		extension = ".frag";
		fullPath = (char*) malloc((strlen(rootDirectory) + it->first.length() + strlen(extension) + 1) * sizeof(char));
		memset(fullPath, 0, (strlen(rootDirectory) + it->first.length()  + strlen(extension) + 1) * sizeof(char));
		strcat_s(fullPath, (strlen(rootDirectory) + it->first.length() + strlen(extension) + 1) * sizeof(char), rootDirectory);
		strcat_s(fullPath, (strlen(rootDirectory) + it->first.length() + strlen(extension) + 1) * sizeof(char), it->first.c_str());
		strcat_s(fullPath, (strlen(rootDirectory) + it->first.length() + strlen(extension) + 1) * sizeof(char), extension);

		sp->fs = new Shader(GL_FRAGMENT_SHADER, fullPath);
		
		sp->Link();

		it->second = sp;

		//it++;
	}
}


void ShaderManager::UseShader(std::string name)
{
	if(mShaders.find(name) != mShaders.end())
	{
		glUseProgram(mShaders[name]->id);
	}
}

GLuint ShaderManager::ProgramId(std::string name)
{
	return mShaders[name]->id;
}

void ShaderManager::DeleteShader(std::string name)
{
	glUseProgram(0);
	glDeleteProgram(mShaders[name]->id);
}