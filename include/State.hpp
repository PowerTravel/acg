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

		enum PolygonMode{
			POINT,
			LINE,
			FILL
		};

		enum ShadeType{
			FLAT,
			PHONG,
			BLINN_PHONG
		}; 


		void setPolygonMode(PolygonMode m);
		PolygonMode getPolygonMode();
		bool isPolygonModeSet();
		void removePolygonMode();

		void setShadeType(ShadeType type);
		ShadeType getShadeType();
		bool isShadeTypeSet();
		void removeShadeType();

		void setCullFace(bool c);
		bool getCullFace();
		bool isCullFaceSet();
		void removeCullFace();
		
		void setColorMaterial(bool c);
		bool getColorMaterial(); 
		bool isColorMaterialSet();
		void removeColorMaterial();

		void setMaterial(Material m);
		Material getMaterial();
		bool isMaterialSet();
		void removeMaterial();

		void setShader(shader_ptr s);
		shader_ptr getShader();
		bool isShaderSet();
		void removeShader();


		// Additive elements
		void pushLight(Light l);
		void pushLight(Light l, bool status);
		int getNrLights();
		Light getLight(int n);
		void enableLight(int n);
		void disableLight(int n);
		bool isLightEnabled(int n);
		void popLight(int n);

		void pushTexture(GLuint t);
		int getNrTextures();
		GLuint getTexture(int n);
		void popTexture(int n);


		// NOT FULLY IMPLEMENTED YET. Cant handle materials or multiple lights
		void apply();

		void merge(State* s); 
	
	private:

		struct Lights{
			Light light;
			bool enabled;
		};

		// Aspects that overrides
		PolygonMode _polyMode;
		bool _isPolyModeSet;

		ShadeType _shadeType;
		bool _isShadeTypeSet;

		bool _cullFace;
		bool _isCullFaceSet;

		bool _colorMaterial;
		bool _isColorMaterialSet;

		Material _material;
		bool _isMaterialSet;

		shader_ptr _shader;
		bool _isShaderSet;

		// Aspects that accumulates
		std::list< Lights > _lights;
		std::list< GLuint > _textures;
};

#endif // STATE_HPP
