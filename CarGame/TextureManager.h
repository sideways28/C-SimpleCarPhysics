#pragma once
#include <map>
#include <string>
#include<GL\glew.h>
#include<GL\glut.h>
#include <SOIL\SOIL.h>

class TextureManager
{
private:
	TextureManager(void);
	static TextureManager* m_pInstance;
public:
	static TextureManager* GetInstance();
	~TextureManager(void);
	// //load all the textures from the given path and creates openGl textures
	void LoadAllTextures(void);
private:
	// stores a mapping of texture names to texture ids
	std::map<std::string, GLuint> m_mTextures;
public:
	// Sets the active texture
	void SetActive(std::string textureName);
	// retrusn the number of textures
	int GetNumTextures(void);

	//Clear the Texture
	void ClearTexture();
};

