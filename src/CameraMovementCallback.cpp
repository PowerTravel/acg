#include "CameraMovementCallback.hpp"
#include <iostream>
#include "Scene.hpp"
#include <iostream>
CameraMovementCallback::CameraMovementCallback(camera_ptr cam)
{	
	_cam = cam;
	_p = Vec3();
	_move = Vec3();
	_angularVelocity = 0.01;
	_speed = 0.1;
	_update = false;
}

CameraMovementCallback::~CameraMovementCallback()
{

}

void CameraMovementCallback::execute()
{
	getKeyState();
}

void CameraMovementCallback::getKeyState()
{	

	KeyState::State st = KeyState::getInstance().get();
	if( st & key_state_bit::KEY_W) 
	{
		_cam->rotateAroundOrigin(_angularVelocity, Vec3(1,0,0));
	}
	if( st & key_state_bit::KEY_A)
	{
		_cam->rotateAroundOrigin(-_angularVelocity, Vec3(0,1,0));
	}
	if( st & key_state_bit::KEY_S )
	{
		_cam->rotateAroundOrigin(-_angularVelocity, Vec3(1,0,0));
	}
	if( st & key_state_bit::KEY_D )
	{
		_cam->rotateAroundOrigin(_angularVelocity, Vec3(0,1,0));

	}
	if( st & key_state_bit::KEY_Z )
	{
		_cam->translate(Vec3(0,0,-_speed));

	}
	if( st & key_state_bit::KEY_X )
	{
		_cam->translate(Vec3(0,0, _speed));

	}
	if( st & key_state_bit::KEY_R)
	{
		_cam->lookAt(Vec3(0,0,4), Vec3(0,0,0), Vec3(0,1,0));

	}

	if(KeyState::getInstance().hasWindowChanged())
	{
		_cam->setPerspectiveProjection();
	}
}
