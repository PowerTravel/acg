#ifndef STATE_HPP
#define STATE_HPP

#include <GL/glew.h>
#include "Shader.hpp"

struct State{
	
		State();
		virtual ~State();

		Shader mShader;
		
};

#endif // STATE_HPP
