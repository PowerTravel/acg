#ifndef TEXTURE_CPP
#define TEXTURE_CPP

#include <GL/glew.h>
#include <string>
struct aiTexture;

class Texture{
	
	public:
		Texture();
		Texture(GLenum textureTarget, std::string& filename);
		virtual ~Texture();

		static void clear(GLenum target = GL_TEXTURE_2D);
		void bind(GLenum textureUnit);

	private:
		GLuint _id;
		GLenum _textureTarget;
		bool _loaded;
};

#endif // TEXTURE_CPP
