#include "ShaderProgram.h"


ShaderProgram::ShaderProgram(void)
	: vs(NULL)
	, fs(NULL)
{

}

ShaderProgram::~ShaderProgram(void)
{

}

GLuint ShaderProgram::Link()
{
	id = glCreateProgram();

	if(id==0)
		return 0;

	glAttachShader(id,vs->Compile());
	glAttachShader(id, fs->Compile());

	glLinkProgram(id);

	int status = 0;
	glGetProgramiv(id,GL_LINK_STATUS,&status);

	if(status==GL_FALSE)
	{
		GLint infoLogLength = 0;
		glGetProgramiv(id,GL_INFO_LOG_LENGTH,&infoLogLength);

		char* errorBuffer = NULL;
		errorBuffer = (char*)malloc(infoLogLength*(sizeof(char)));
		memset(errorBuffer,0,infoLogLength);
		glGetProgramInfoLog(id,infoLogLength*sizeof(char),NULL,errorBuffer);
		printf("Shader Program Link Error:\n%s",errorBuffer);
		return 0;
	}
	return id;
}



