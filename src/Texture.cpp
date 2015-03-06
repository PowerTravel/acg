#include "Texture.hpp"
#include "vr/JPGReader.h"
#include "vr/PNGReader.h"
#include <assimp/scene.h>
#include <iostream>

Texture::Texture()
{
	_loaded = false;
}

/*
 * Name:	Texture
 * Purpose: Given a filename and textureTarget (probably redundant as
 *			support only exists for 2D_textures) it can load a 
 *			texture onto the gpu.
 * Input:	-GLenum textureTarget: The type of texture to load.
 * 			-std::string filename: The path to the file to be loaded
 * Output:	-
 * Misc:	Only jpg and png supported
 */
Texture::Texture(GLenum textureTarget, std::string& filename)
{
	_textureTarget = textureTarget;
	vr::Image* img = NULL;
	_loaded = false;

	// Load the file.
	if(filename.find(".jpg")!=std::string::npos)
	{
		vr::JPGReader reader = vr::JPGReader();
		img = reader.readImage( filename );

	}else if( filename.find(".png")!=std::string::npos){

		vr::PNGReader reader = vr::PNGReader();
		img = reader.readImage( filename );	
	}else{
		std::cerr << filename << " is not a supported filetype"<< std::endl; 
	}

	// send the texture to the gpu	
	if(img != NULL ){
		glGenTextures(1, &_id);
		glBindTexture(_textureTarget, _id);	
  	
		glTexParameterf(_textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(_textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		glTexImage2D(_textureTarget, 0, GL_RGB, img->width(), img->height(), 0, GL_RGB, GL_UNSIGNED_BYTE, img->data() );

		
/*		Ignore this. Saving for later.
		vr::Image* image = img;
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
  		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  		gluBuild2DMipmaps( GL_TEXTURE_2D, 3, image->width(), image->height(), GL_RGB, GL_UNSIGNED_BYTE, image->data());
		*/

  		glBindTexture(GL_TEXTURE_2D, 0);

		_loaded = true;
	}
}
Texture::~Texture()
{

}

/*
 * Name:	clear
 * Purpose: Unbinds the texture loaded to _textureTarget
 * Input:	-
 * Output:	-
 * Misc:	-
 */
void Texture::clear()
{
	glBindTexture(_textureTarget,0);
}

/*
 * Name:	bind	
 * Purpose: Binds its texture to the glState
 * Input:	GLenum textureUnit: The slot  	
 * Output:	-
 * Misc:	-
 */
void Texture::bind(GLenum textureUnit)
{
	if(_loaded)
	{
		glActiveTexture(textureUnit);
		glBindTexture(_textureTarget, _id);
	}
}

bool Texture::loaded()
{
	return _loaded;
}
