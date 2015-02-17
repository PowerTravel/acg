#include "Light.hpp"

Light::Light()
{
	_position = Vec3();
	_ambient = Vec4();
	_diffuse = Vec4();
	_specular = Vec4();
}

Light::Light(Vec3 position, Vec4 ambient, Vec4 diffuse, Vec4 specular)
{
	_position = position;
	_ambient = ambient;
	_diffuse = diffuse;
	_specular = specular;
}

Light::~Light()
{

}


void Light::setPosition(Vec3 pos)
{
	_position = pos;
}

void Light::setSpecular(Vec4 spec)
{
	_specular = spec;
}
void Light::setDiffuse(Vec4 diff)
{
	_diffuse = diff;
}
void Light::setAmbient(Vec4 amb)
{
	_ambient = amb;
}
