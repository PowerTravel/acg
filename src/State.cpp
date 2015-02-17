#include "State.hpp"
State::State()
{
	_shaderSet = false;
	_materialSet= false;
	_cullFace = NO_STATUS;
	_colorMaterial = NO_STATUS;
	_shadingType = NO_SHADING;
	_lights = std::list< light_ptr >();
	_textures = std::list< GLuint >();
}

State::~State()
{

}


void State::setCullFace(bool c)
{
	if(c == true){
		_cullFace = YES;
	}else{
		_cullFace = NO;
	}
}
State::Status State::cullFace()
{
	return _cullFace;
}

void State::setColorMaterial(bool c)
{
	if(c == true){
		_colorMaterial = YES;
	}else{
		_colorMaterial = NO;
	}
}
State::Status State::colorMaterial()
{
	return _colorMaterial;
}

void State::setShader(Shader s)
{
	_shader = s;
	_shaderSet = true;
}
Shader State::getShader()
{
	return _shader;
}
void State::removeShader()
{
	_shaderSet = false;
}
bool State::hasShader()
{
	return _shaderSet;
}

void State::setMaterial(Material m)
{	
	_material = m;
	_materialSet = true;
}
Material State::getMaterial()
{
	return _material;
}
void State::removeMaterial()
{
	_materialSet = false;
}

bool State::hasMaterial()
{
	return _materialSet;
}

void State::pushLight(light_ptr lptr)
{
	_lights.push_back(lptr);	
}
int State::getNrLights()
{
	return _lights.size();
}
light_ptr State::getLight(int n)
{	
	std::list<light_ptr>::iterator it = _lights.begin();
	if(n < _lights.size()){
		std::advance(it,n);
		return *it;
	}else{
		return NULL;
	}
}
void State::popLight(int n)
{
	std::list<light_ptr>::iterator it = _lights.begin();
	if(n < _lights.size()){
		std::advance(it,n);
		_lights.erase(it);
	}
}

void State::pushTexture(GLuint t)
{
	_textures.push_back(t);
}
int State::getNrTextures()
{
	return _textures.size();
}
GLuint State::getTexture(int n)
{
	std::list<GLuint>::iterator it = _textures.begin();
	if(n < _textures.size()){
		std::advance(it,n);
		return *it;
	}else{
		return 0;
	}
	
}
void State::popTexture(int n)
{
	std::list<GLuint>::iterator it = _textures.begin();
	if(n < _textures.size()){
		std::advance(it,n);
		_textures.erase(it);
	}
}

void State::setShadeType(ShadeType type)
{
	_shadingType = type;
}

State::ShadeType State::shadeType()
{
 	return _shadingType;
}
