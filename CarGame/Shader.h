#pragma once
#include <Windows.h>
#include <iostream>
#include <GL\glew.h>
#include <string>
#include <map>

class Shader
{
public:
	Shader(int _type,char* _source);
	~Shader(void);

	int type;
	char* source;
	GLuint id;

	GLuint Compile();
	static Shader* CreateShader(int type);
	void DeleteShader(GLuint _id);
};

