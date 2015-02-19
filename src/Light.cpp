#include "Light.hpp"
#include "Material.hpp"
Light::Light()
{
	_position = Vec3(4,4,4);
	_ambient = Vec4(0.7,0.7,0.7,1);
	_diffuse = Vec4(0.7,0.7,0.7,1);
	_specular = Vec4(0.7,0.7,0.7,1);
	_attenuation = 0.2;
}

Light::Light(Vec3 position, Vec4 ambient, Vec4 diffuse, Vec4 specular, float attenuation)
{
	_position = position;
	_ambient = ambient;
	_diffuse = diffuse;
	_specular = specular;
	_attenuation = attenuation;
}

Light::~Light()
{

}


void Light::setPosition(Vec3 pos)
{
	_position = pos;
}
Vec3 Light::getPosition()
{
	return _position;
}
void Light::setSpecular(Vec4 spec)
{
	_specular = spec;
}
Vec4 Light::getSpecular()
{
	return _ambient;
}
void Light::setDiffuse(Vec4 diff)
{
	_diffuse = diff;
}
Vec4 Light::getDiffuse()
{
	return _diffuse;
}
void Light::setAmbient(Vec4 amb)
{
	_ambient = amb;
}

Vec4 Light::shineOn(Material m)
{	
	Vec4 mc4 = m.getSpecular();
	float alpha = mc4[3];
	Vec3 mc = mc4.asVec3();
	Vec3 l = _specular.asVec3();
	float specular = mc*l;

	mc4 = m.getDiffuse();
	alpha = alpha * mc4[3];
	mc = mc4.asVec3();
	l = _specular.asVec3();
	float diffuse = mc*l;

	mc4 = m.getAmbient();
	alpha = alpha * mc4[3];
	mc = mc4.asVec3();
	l = _ambient.asVec3();
	float ambient = mc*l;

	return Vec4(specular,diffuse,ambient,alpha);
}
void Light::setAttenuation(float at)
{
	_attenuation = at;
}
float Light::getAttenuation()
{
	return _attenuation;
}
