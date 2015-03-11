#include "RenderToTexture.hpp"
#include "NodeVisitor.hpp"

RenderToTexture::RenderToTexture(int w, int h)
{
	_framebuffer= 0;
	glGenFramebuffers(1, &_framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);

	GLuint depthTex = 0;
	glGenTextures(1, &depthTex);
	glBindTexture(GL_TEXTURE_2D, depthTex);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16 , w, h, 0, GL_DEPTH_COMPONENT, GL_FLOAT,0  );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTex, 0);

	// Draw only depth, no color.
	glDrawBuffer(GL_NONE);

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cerr << "Failed to create framebuffer in STATE.cpp" << std::endl;
	}

	_depthTex = Texture(depthTex);

	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}
RenderToTexture::~RenderToTexture()
{

}

void RenderToTexture::acceptVisitor(NodeVisitor& v)
{	
	v.apply(this);
}

void RenderToTexture::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);
}
void RenderToTexture::clear()
{

}
