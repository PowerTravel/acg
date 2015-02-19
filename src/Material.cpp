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
		_diffuse= Vec4(0.7,0.04,0.04,1);
		_specular = Vec4(0.5,0.4,0.4,1);
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
Vec4 Material::getSpecular(Light* l)
{
	Vec4 lSpec = l->getSpecular();
	return Vec4( 	lSpec[0]*_specular[0],
					lSpec[1]*_specular[1],
					lSpec[2]*_specular[2],
					lSpec[3]*_specular[3]);
}
void Material::setDiffuse(Vec4 diff)
{
	_diffuse = diff;
}
Vec4 Material::getDiffuse()
{
	return _diffuse;
}
Vec4 Material::getDiffuse(Light* l)
{
	Vec4 lDiff = l->getDiffuse();
	return Vec4( 	lDiff[0]*_diffuse[0],
					lDiff[1]*_diffuse[1],
					lDiff[2]*_diffuse[2],
					lDiff[3]*_diffuse[3]);
}
void Material::setAmbient(Vec4 amb)
{
	_ambient = amb;
}
Vec4 Material::getAmbient()
{
	return _ambient;
}
Vec4 Material::getAmbient(Light* l)
{
	Vec4 lAmb = l->getAmbient();
	return Vec4( 	lAmb[0]*_ambient[0],
					lAmb[1]*_ambient[1],
					lAmb[2]*_ambient[2],
					lAmb[3]*_ambient[3]);
}

void Material::apply(State* st)
{
	st->setMaterial(*this);
}
