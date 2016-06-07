#pragma once
#include "Shader.h"

class ShaderProgram
{
private:


public:
	Shader* vs;
	Shader* fs;
	ShaderProgram(void);
	~ShaderProgram(void);
	GLuint id;
	GLuint Link();
};

