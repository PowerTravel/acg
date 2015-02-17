#ifndef STATE_HPP
#define STATE_HPP

#include <GL/glew.h>
#include <memory>
#include <list>
#include "Shader.hpp"
#include "Material.hpp"
#include "Light.hpp"


#ifndef STATE_PTR
#define STATE_PTR
class State;
typedef std::shared_ptr<State> state_ptr;
#endif // STATE_PTR

class State{

	public:
		
		State();
		virtual ~State();

		enum Status{
			NO_STATUS,
			YES,
			NO
		};

		enum ShadeType{
			NO_SHADING,
			FLAT,
			PHONG,
			BLINN_PHONG
		}; 

		void setCullFace(bool c);
		Status cullFace();

		void setColorMaterial(bool c);
		Status colorMaterial(); 

		void setShader(Shader s);
		Shader getShader();
		void removeShader();
		bool hasShader();

		void setMaterial(Material m);
		Material getMaterial();
		void removeMaterial();
		bool hasMaterial();

		void pushLight(light_ptr lptr);
		int getNrLights();
		light_ptr getLight(int n);
		void popLight(int n);

		void pushTexture(GLuint t);
		int getNrTextures();
		GLuint getTexture(int n);
		void popTexture(int n);

		void setShadeType(ShadeType type);
		ShadeType shadeType();

	private:
		// Aspects that overrides
		Shader _shader;
		bool _shaderSet;
		Material _material;
		bool _materialSet;

		ShadeType _shadingType;
		Status _cullFace;	//see GL_CULL_FACE
		Status _colorMaterial;

		// Aspects that accumulates
		std::list< light_ptr > _lights;
		std::list< GLuint > _textures;
};

#endif // STATE_HPP
