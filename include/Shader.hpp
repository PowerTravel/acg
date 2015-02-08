#ifndef SHADER_HPP
#define SHADER_HPP

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>

class Shader{

	public:
		Shader();
		Shader(const char* vShaderFile, const char* fShaderFile);
		virtual ~Shader();
		void use();

	private:
		
	struct ShaderFile{
		const char* filename;
		GLenum type;
		GLchar* source;
		GLuint id;
	};
		GLuint program;	

		char* readShaderSource(const char* shaderFile);

};

#endif // SHADER_HPP
