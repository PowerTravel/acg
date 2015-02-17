#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <memory>
#include "Vec4.hpp"
#include "Vec3.hpp"

#ifndef LIGHT_PTR
#define LIGHT_PTR
class Light;
typedef std::shared_ptr<Light> light_ptr;
#endif // LIGHT_PTR


class Light{

	public:
		Light();
		Light(Vec3 pos, Vec4 ambient, Vec4 diffuse, Vec4 specular);
		virtual ~Light();

		void setPosition(Vec3 pos);
		void setSpecular(Vec4 spec);
		void setDiffuse(Vec4 diff);
		void setAmbient(Vec4 amb);

	private:
		Vec3 _position;
		Vec4 _ambient;
		Vec4 _diffuse;
		Vec4 _specular;

};

#endif // LIGHT_HPP
