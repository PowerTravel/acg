#ifndef RENDER_TO_TEXTURE_HPP
#define RENDER_TO_TEXTURE_HPP

//#include <memory>
#include "Group.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
class RenderToTexture: public Group{
	public:
		RenderToTexture(std::shared_ptr<Shader> s, int w=620, int h = 480);
		virtual ~RenderToTexture();

		void render();

		void acceptVisitor(NodeVisitor& v);

		
	private:
		GLuint _framebuffer;
		Texture _depthTex;
		std::shared_ptr<Shader> _s;
};

#endif // RENDER_TO_TEXTURE_HPP
