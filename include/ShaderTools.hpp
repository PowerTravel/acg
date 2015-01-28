#ifndef SHADERTOOLS_CPP
#define SHADERTOOLS_CPP

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>

GLuint initProgram(const char* vShaderFile, const char* fShaderFile);
char* readShaderSource(const char* shaderFile);

struct Shader{
	const char* filename;
	GLenum type;
	GLchar* source;
	GLuint id;
};

#endif //SHADERTOOLS_CPP
