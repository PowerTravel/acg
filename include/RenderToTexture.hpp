#ifndef RENDER_TO_TEXTURE_HPP
#define RENDER_TO_TEXTURE_HPP

#include "Group.hpp"
#include "Texture.hpp"


class RenderToTexture: public Group{
	public:
		RenderToTexture(int w=620, int h = 480);
		virtual ~RenderToTexture();

		// Set the rendertarget to the _framebuffer
		void bind();
		// Reset the render target
		void clear();

		void acceptVisitor(NodeVisitor& v);

	private:
		GLuint _framebuffer;
		Texture _depthTex;
};

#endif // RENDER_TO_TEXTURE_HPP
