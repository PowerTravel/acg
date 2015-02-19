#ifndef MATERIAL_HPP
#define MATERIAL_HPP
#include <memory>
#include "Vec4.hpp"

class Light;
class State;
#ifndef MATERIAL_PTR
#define MATERIAL_PTR
class Material;
typedef std::shared_ptr<Material> material_ptr;
#endif // MATERIAL_PTR

class Material{

	public:
		enum MaterialPreset{
			RUBBER_RED	
		};

		Material();
		Material(MaterialPreset);
		Material(float shininess, Vec4 specular, Vec4 diffuse, Vec4 ambient);
		virtual ~Material();

		void setMaterial(MaterialPreset);

		void setShininess(float s);
		float getShininess();
		void setSpecular(Vec4 spec);
		Vec4 getSpecular();
		void setDiffuse(Vec4 diff);
		Vec4 getDiffuse();
		void setAmbient(Vec4 amb);
		Vec4 getAmbient();

		void apply(State* st);
		Vec4 illuminate(Light l);
	private:
		float _shininess;
		Vec4 _specular;
		Vec4 _diffuse;
		Vec4 _ambient;

		static Vec4 totLight;
};

#endif// MATERIAL_HPP
