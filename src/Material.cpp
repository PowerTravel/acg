#include "Material.hpp"
#include "State.hpp"
#include "Light.hpp"
Material::Material()
{
	setMaterial(RUBBER_RED);
}

Material::Material(MaterialPreset m)
{
	setMaterial(m);
}

void Material::setMaterial(MaterialPreset m)
{
	if(m == RUBBER_RED)
	{
		_shininess=10;
		_specular = Vec4(0.7,0.04,0.04);
		_diffuse = Vec4(0.5,0.4,0.4,1);
		_ambient = Vec4(0.05, 0,0,1);
	}
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
float Material::getShininess()
{
	return _shininess;
}
void Material::setSpecular(Vec4 spec)
{
	_specular = spec;
}
Vec4 Material::getSpecular()
{
	return _specular;
}
void Material::setDiffuse(Vec4 diff)
{
	_diffuse = diff;
}
Vec4 Material::getDiffuse()
{
	return _diffuse;
}
void Material::setAmbient(Vec4 amb)
{
	_ambient = amb;
}
Vec4 Material::getAmbient()
{
	return _ambient;
}

void Material::apply(State* st)
{
	st->setMaterial(*this);
}

Vec4 Material::illuminate(Light l)
{
	return l.shineOn(*this);
}
