#include "Shader.h"


Shader::Shader(int _type,char* _source)
	:type(0)
	,source(NULL)
{
	type = _type;
	source = _source;
}


Shader::~Shader(void)
{

}


GLuint Shader::Compile()
{
	id = 0;
	id = glCreateShader(type);

	if(id==0)
		return 0;
	
	FILE* fp;
	fopen_s(&fp, source, "r");
	int length=0;
	fseek(fp,0,SEEK_END);
	length = ftell(fp);
	rewind(fp);

	char* buffer = NULL;
	buffer = (char*)malloc(length*sizeof(char));
	memset(buffer, 0, length);
	fread(buffer,sizeof(char),length,fp);

	glShaderSource(id, 1, (const GLchar**)&buffer,NULL);
	glCompileShader(id);

	int status = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &status);

	if(status==GL_FALSE)
	{
		int infoLogLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);
		
		char* errorBuffer=NULL;
		errorBuffer = (char*)malloc((infoLogLength+1)*sizeof(char));
		memset(errorBuffer,0,infoLogLength);

		glGetShaderInfoLog(id,infoLogLength*sizeof(char),NULL,errorBuffer);

		printf("Shader Compile Error:\n%s",errorBuffer);

		return 0;
	}

	return id;
}

void Shader::DeleteShader(GLuint _id)
{
	glDeleteShader(_id);
}


