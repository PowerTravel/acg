#include "State.hpp"
State::State()
{
	// If a state is not explicity set they wont
	// override another state if added.
	_isPolyModeSet = false;
	_isShadeTypeSet = false;
	_isCullFaceSet = false;
	_isColorMaterialSet = false;
	_isMaterialSet = false;
	_isShaderSet = false;
	//Sets default values
	_polyMode = FILL;
	_shadeType = FLAT;
	_cullFace = true;
	_colorMaterial = false;
	_material = Material();
	_shader = NULL;
	_lights = std::list< Lights >();
	_textures = std::list< GLuint >();
}

State::~State()
{

}

void State::merge(State* s)
{
	if(s->isPolygonModeSet())
	{
		setPolygonMode( s->getPolygonMode() );
	}
	if( s->isShadeTypeSet() )
	{
		setShadeType( s->getShadeType() );
	}
	if( s->isCullFaceSet() )
	{
		setCullFace( s->getCullFace() );
	}
	if( s->isColorMaterialSet() )
	{
		setColorMaterial(s->getColorMaterial());
	}
	if( s->isMaterialSet() )
	{
		setMaterial( s->getMaterial() );
	}
	if(s->isShaderSet())
	{
		setShader(s->getShader());
	}

	int n = s->getNrLights();
	int i = 0;
	while(i<n)
	{
		pushLight(s->getLight(i), s->isLightEnabled(i) );
		i++;
	}

	n = s->getNrTextures();
	i = 0;
	while(i<n)
	{
		pushTexture(s->getTexture(i));
		i++;
	}
}

void State::setPolygonMode(PolygonMode m)
{
	_polyMode = m;
	_isPolyModeSet = true;
}
State::PolygonMode State::getPolygonMode()
{
	return _polyMode;
}
bool State::isPolygonModeSet()
{
	return _isPolyModeSet;
}
void State::removePolygonMode()
{
	_polyMode = FILL;
	_isPolyModeSet = false;
}


void State::setShadeType(ShadeType s)
{
	_shadeType = s;
	_isShadeTypeSet = true;
}
State::ShadeType State::getShadeType()
{
	return _shadeType;
}
bool State::isShadeTypeSet()
{
	return _isShadeTypeSet;
}
void State::removeShadeType()
{
	_shadeType = FLAT;
	_isShadeTypeSet = false;
}


void State::setCullFace(bool c)
{
	_cullFace = c;
	_isCullFaceSet = true;
}
bool State::getCullFace()
{
	return _cullFace;
}
bool State::isCullFaceSet()
{
	return _isCullFaceSet;
}
void State::removeCullFace()
{
	_cullFace = true;
	_isCullFaceSet = false;
}

void State::setColorMaterial(bool s)
{
	_colorMaterial = s;
	_isColorMaterialSet = true;
}
bool State::getColorMaterial()
{
	return _colorMaterial;
}
bool State::isColorMaterialSet()
{
	return _isColorMaterialSet;
}
void State::removeColorMaterial()
{
	_colorMaterial = false;
	_isColorMaterialSet = false;
}


void State::setMaterial(Material m)
{	
	_material = m;
	_isMaterialSet = true;
}
Material State::getMaterial()
{
	return _material;
}
void State::removeMaterial()
{
	_material = Material();
	_isMaterialSet = false;
}
bool State::isMaterialSet()
{
	return _isMaterialSet;
}


void State::setShader(shader_ptr s)
{
	_shader = s;
	_isShaderSet = true;
}
shader_ptr State::getShader()
{
	return _shader;
}
bool State::isShaderSet()
{
	return _isShaderSet;
}
void State::removeShader()
{
	_shader = NULL;
	_isShaderSet = false;
}


void State::pushLight(Light l)
{
	Lights ls;
	ls.light = l;
	ls.enabled = true;
	_lights.push_back(ls);	
}
void State::pushLight(Light l, bool status)
{
	Lights ls;
	ls.light = l;
	ls.enabled = status;
	_lights.push_back(ls);	
}	

int State::getNrLights()
{
	return _lights.size();
}
Light State::getLight(int n)
{	
	std::list<Lights>::iterator it = _lights.begin();
	std::advance(it,n);
	return it->light;
}
void State::enableLight(int n)
{
	std::list<Lights>::iterator it = _lights.begin();
	std::advance(it,n);
	it->enabled = true;
}
void State::disableLight(int n)
{
	std::list<Lights>::iterator it = _lights.begin();
	std::advance(it,n);
	it->enabled = false;
}
bool State::isLightEnabled(int n)
{
	std::list<Lights>::iterator it = _lights.begin();
	std::advance(it,n);
	return it->enabled;

}
void State::popLight(int n)
{
	std::list<Lights>::iterator it = _lights.begin();
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

void State::apply()
{
	if( isShaderSet() )
	{
		// Set polygon Mode
		if( _polyMode == POINT ){
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		}else if( _polyMode == LINE){
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}else if(_polyMode == FILL){
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		
		// SMOOTH VS FLAT SHADING NOT IMPLEMENTED
		glShadeModel(GL_FLAT);
	
		// Enable or disable backface culling
		glCullFace(GL_FRONT);
		if(_cullFace)
		{
			glEnable(GL_CULL_FACE);
		}else{
			glDisable(GL_CULL_FACE);
		}
	
		// tell if we should use Vertex color or a material
		/// NOT IMPLEMENTED
		
	
		// enable material aka, upload it to the shader
		

		// Set ONE light
		Light l = Light();
		l.setPosition(Vec3(4,4,4));
		Vec4 ambProd = _material.getAmbient(&l);  
		Vec4 diffProd = _material.getDiffuse(&l);  
		Vec4 specProd = _material.getSpecular(&l);  

		float data4[4];
		
		specProd.get(data4);
		_shader->setUniform4("specularProduct", data4);
		
		diffProd.get(data4);
		_shader->setUniform4("diffuseProduct", data4);
		
		ambProd.get(data4);
		_shader->setUniform4("ambientProduct", data4);

		float data3[3];
		l.getPosition().get(data3);
		_shader->setUniform3("lightPosition", data3);
		float attenuation = l.getAttenuation();
		_shader->setUniform1("attenuation", &attenuation);
		float shininess = _material.getShininess();
		_shader->setUniform1("shininess", &shininess);
	}
	
}

