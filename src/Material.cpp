#include "Material.hpp"
#include "State.hpp"
Material::Material()
{
	float shininess=0;
	_specular = Vec4();
	_diffuse = Vec4();
	_ambient = Vec4();
}

Material::Material(float shininess, Vec4 specular, Vec4 diffuse, Vec4 ambient)
{
	_shininess=shininess;
	_specular = specular;
	_diffuse = diffuse;
	_ambient = ambient;
}

Material::~Material()
{

}

void Material::setShininess(float s)
{
	_shininess = s;
}
void Material::setSpecular(Vec4 spec)
{
	_specular = spec;
}
void Material::setDiffuse(Vec4 diff)
{
	_diffuse = diff;
}
void Material::setAmbient(Vec4 amb)
{
	_ambient = amb;
}
		
void Material::apply(State* st)
{
	st->setMaterial(*this);
}
