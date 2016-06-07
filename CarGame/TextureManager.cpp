#include "TextureManager.h"

TextureManager::TextureManager(void)
{
}


TextureManager::~TextureManager(void)
{

}

TextureManager* TextureManager::m_pInstance = NULL;

TextureManager* TextureManager::GetInstance()
{
	if (!m_pInstance){
		m_pInstance = new TextureManager();
	}
	return m_pInstance;
}

// //load all the textures from the given path and creates openGl textures
void TextureManager::LoadAllTextures(void)
{
	char* rootDirectory = "Resources\\Textures\\";
	char* extension = "*.png";
#ifdef WIN32

	char* fullPath = NULL;
	fullPath = (char*)malloc((strlen(rootDirectory) + strlen(extension) + 1) * sizeof(char));
	memset(fullPath, 0, (strlen(rootDirectory) + strlen(extension) + 1) * sizeof(char));
	strcat_s(fullPath, (strlen(rootDirectory) + strlen(extension) + 1) * sizeof(char), rootDirectory);
	strcat_s(fullPath, (strlen(rootDirectory) + strlen(extension) + 1) * sizeof(char), extension);

	WIN32_FIND_DATAA wfd = { 0 };
	HANDLE handle = FindFirstFileA(fullPath, &wfd);
	delete(fullPath);

	while (handle != INVALID_HANDLE_VALUE)
	{
		fullPath = (char*)malloc((strlen(rootDirectory) + strlen(wfd.cFileName) + 1) * sizeof(char));
		memset(fullPath, 0, (strlen(rootDirectory) + strlen(wfd.cFileName) + 1) * sizeof(char));
		strcat_s(fullPath, (strlen(rootDirectory) + strlen(wfd.cFileName) + 1) * sizeof(char), rootDirectory);
		strcat_s(fullPath, (strlen(rootDirectory) + strlen(wfd.cFileName) + 1) * sizeof(char), wfd.cFileName);
		GLuint id = SOIL_load_OGL_texture(fullPath, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
		std::string name = wfd.cFileName;
		m_mTextures[name] = id;

		if (FindNextFileA(handle, &wfd) == FALSE)
			break;
	}

#else
#ifdef LINUX
#endif
#endif
}


// Sets the active texture
void TextureManager::SetActive(std::string textureName)
{
	GLuint textureId = m_mTextures[textureName];

	if (textureId == 0)
	{
		printf("ERROR: Texture not found: %s\n", textureName.c_str());
		return;
	}

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureId);
}


// returns the number of textures
int TextureManager::GetNumTextures(void)
{
	return m_mTextures.size();
}

void TextureManager::ClearTexture()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}