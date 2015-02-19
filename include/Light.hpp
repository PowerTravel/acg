#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <memory>
#include "Vec4.hpp"
#include "Vec3.hpp"

class Material;
#ifndef LIGHT_PTR
#define LIGHT_PTR
class Light;
typedef std::shared_ptr<Light> light_ptr;
#endif // LIGHT_PTR


class Light{

	public:
		Light();
		Light(Vec3 pos, Vec4 ambient, Vec4 diffuse, Vec4 specular, float _attenuation);
		virtual ~Light();

		void setPosition(Vec3 pos);
		Vec3 getPosition();
		void setSpecular(Vec4 spec);
		Vec4 getSpecular();
		void setDiffuse(Vec4 diff);
		Vec4 getDiffuse();
		void setAmbient(Vec4 amb);
		Vec4 getAmbient();
		void setAttenuation(float at);
		float getAttenuation();

		Vec4 shineOn(Material m);

	private:
		Vec3 _position;
		Vec4 _ambient;
		Vec4 _diffuse;
		Vec4 _specular;
		float _attenuation;
};

#endif // LIGHT_HPP
