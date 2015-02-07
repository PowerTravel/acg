#ifndef STATE_HPP
#define STATE_HPP

#include <GL/glew.h>

class State{
	
	public:
		State();
		virtual ~State();
	
		GLuint program;
		
};

#endif // STATE_HPP
