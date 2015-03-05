#ifndef MATERIAL_HPP
#define MATERIAL_HPP
#include <memory>
#include "Vec4.hpp"

#include <assimp/scene.h>

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
			RUBBER_RED,
			GLASS_YELLOW
		};

		Material();
		Material(MaterialPreset);
		Material(const aiMaterial* mat);
		Material(float shininess, Vec4 specular, Vec4 diffuse, Vec4 ambient);
		virtual ~Material();

		void setMaterial(MaterialPreset);
		void setMaterial(const aiMaterial* mat);

		void setShininess(float s);
		float getShininess();
		void setSpecular(Vec4 spec);
		Vec4 getSpecular();
		Vec4 getSpecular(Light* l);
		void setDiffuse(Vec4 diff);
		Vec4 getDiffuse();
		Vec4 getDiffuse(Light* l);
		void setAmbient(Vec4 amb);
		Vec4 getAmbient();
		Vec4 getAmbient(Light* l);

		void apply(State* st);
	private:
		float _shininess;
		Vec4 _specular;
		Vec4 _diffuse;
		Vec4 _ambient;

	//	static Vec4 totLight;
	
};

#endif// MATERIAL_HPP
