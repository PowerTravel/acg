#ifndef STATE_HPP
#define STATE_HPP

#include <GL/glew.h>
#include <memory>
#include "Shader.hpp"

#ifndef STATE_PTR
#define STATE_PTR
class State;
typedef std::shared_ptr<State> state_ptr;
#endif // STATE_PTR

struct State{
	
		State();
		virtual ~State();

		Shader mShader;
		
};

#endif // STATE_HPP
