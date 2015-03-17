#include "KeyState.hpp"
#include "Scene.hpp"
#include "UpdateVisitor.hpp"
#include <GL/freeglut.h>

KeyState::State KeyState::_state = KeyState::State::KEY_NULL;
bool KeyState::mWindowChanged = false;

KeyState::KeyState()
{

}

KeyState::~KeyState()
{

}

KeyState& KeyState::getInstance()
{
	static KeyState instance;
	return instance;
}
KeyState::State KeyState::get()
{	
	return _state;
}

void KeyState::setGlutCallback()
{
	glutKeyboardFunc(glut_key_callback);
	glutKeyboardUpFunc(glut_key_callback);
	glutReshapeFunc(resize_callback);
}

void KeyState::windowChanged()
{
	mWindowChanged=true;
}

bool KeyState::hasWindowChanged()
{
	bool c = false;
	if(mWindowChanged){
		mWindowChanged = false;
		c=true;
	}	
	return c;
}
void KeyState::set(int st)
{
	int currState = (int) _state;

	// Updates to the new state
	int newState =  currState ^ st; 

	_state = (State) newState;
}

void resize_callback(int width, int height)
{
	// this call to GL viewport should not be here.
	// It should be in lab1.cpp but I don't know how to make 
	// that work yet
	glViewport(0,0,width,height);
	KeyState::getInstance().windowChanged();
	Scene::getInstance().getUpdateVisitor()->windowChanged();	
}

void glut_key_callback(unsigned char c, int x, int y)
{
	int st = 0;
	if( c == 'a' || c == 'A' )
	{
		st  += (int) KeyState::KEY_A;	
	}
	if( c == 'd' || c == 'D' )
	{
		st  += (int) KeyState::KEY_D;	
	}
	if( c == 'p' || c == 'P' )
	{
		st  += (int) KeyState::KEY_P;	
	}
	if( c == 'q' || c == 'Q' )
	{
		st  += (int) KeyState::KEY_Q;	
	}
	if( c == 'r' || c == 'R')
	{
		st  += (int) KeyState::KEY_R;
	}
	if( c == 's' || c == 'S' )
	{
		st  += (int) KeyState::KEY_S;	
	}
	if( c == 't' || c == 'T' )
	{
		st  += (int) KeyState::KEY_T;	
	}
	if( c == 'w' || c == 'W' )
	{
		st += (int) KeyState::KEY_W;	
	}
	if( c == 'x' || c == 'X' )
	{
		st  += (int) KeyState::KEY_X;	
	}
	if( c == 'z' || c == 'Z' )
	{
		st  += (int) KeyState::KEY_Z;	
	}
	KeyState::getInstance().set( st );
}

