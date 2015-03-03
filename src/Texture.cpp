#include "Texture.hpp"
#include "vr/JPGReader.h"
#include "vr/PNGReader.h"
#include <assimp/scene.h>
#include <iostream>

Texture::Texture()
{
	_loaded = false;
}
Texture::Texture(GLenum textureTarget, std::string& filename)
{
	_textureTarget = textureTarget;
	vr::Image* img = NULL;
	if(filename.find(".jpg")!=std::string::npos)
	{
		vr::JPGReader reader = vr::JPGReader();
		img = reader.readImage( filename );
		_loaded = true;

	}else if( filename.find(".png")!=std::string::npos){

		vr::PNGReader reader = vr::PNGReader();
		img = reader.readImage( filename );	
		_loaded = true;
	}else{
		_loaded = false;
		std::cerr << filename << " is not a supported filetype"<< std::endl; 
	}
	
	if(_loaded = true){

		glGenTextures(1, &_id);
		glBindTexture(_textureTarget, _id);	
  	
		glTexParameterf(_textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(_textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		glTexImage2D(_textureTarget, 0, GL_RGB, img->width(), img->height(), 0, GL_RGB, GL_UNSIGNED_BYTE, img->data() );

/*
		vr::Image* image = img;
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
  		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  		gluBuild2DMipmaps( GL_TEXTURE_2D, 3, image->width(), image->height(), GL_RGB, GL_UNSIGNED_BYTE, image->data());
		*/
  		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
Texture::~Texture()
{

}

void Texture::clear(GLenum target)
{
	glBindTexture(target,0);
}
void Texture::bind(GLenum textureUnit)
{
	if(_loaded)
	{
		glActiveTexture(textureUnit);
		glBindTexture(_textureTarget, _id);
	}
}
