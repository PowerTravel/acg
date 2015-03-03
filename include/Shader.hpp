#ifndef SHADER_HPP
#define SHADER_HPP

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>

#include <unordered_map>
#include <string>
#include <memory>

#ifndef UNI_TABLE
#define UNI_TABLE
typedef std::unordered_map<std::string, GLuint> UniTable;
#endif //UNI_TABLE

#ifndef SHADER_PTR
#define SHADER_PTR
class Shader;
typedef std::shared_ptr<Shader> shader_ptr;
#endif // SHADER_PTR

class Shader{

	public:

		Shader();
		Shader(const char* vShaderFile, const char* fShaderFile);
		virtual ~Shader();
		void use();
		
		// UniformLoaders
		void createUniform(std::string name);
		void createAttribute(std::string name);
		
		void setUniformMatrix(std::string name, float* data);
		void setUniform1(std::string name, float data);
		void setUniform2(std::string name, float* data);
		void setUniform3(std::string name, float* data);
		void setUniform4(std::string name, float* data);

		void setUniform1i(std::string name, unsigned int unit);

		GLuint getUniform(std::string name);

	private:

	struct ShaderFile{
		const char* filename;
		GLenum type;
		GLchar* source;
		GLuint id;
	};

		GLuint program;	
		// UniformTable
		UniTable ut;

		char* readShaderSource(const char* shaderFile);
	
};

#endif // SHADER_HPP
