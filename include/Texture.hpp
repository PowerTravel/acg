#ifndef TEXTURE_CPP
#define TEXTURE_CPP

#include <GL/glew.h>
#include <string>
struct aiTexture;

/*
 * Class: 	Texture
 * Purpose: Loads textures to the gpu.
 * Misc:	Only supports diffuse textures
 */
class Texture{
	
	public:
		
		Texture();
		Texture(GLenum textureTarget, std::string& filename);
		virtual ~Texture();

		void clear();
		void bind(GLenum textureUnit);
		bool loaded();

	private:
		GLuint _id;
		GLenum _textureTarget;
		bool _loaded;
};

#endif // TEXTURE_CPP
