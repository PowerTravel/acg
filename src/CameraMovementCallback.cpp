#include "CameraMovementCallback.hpp"
#include <iostream>
#include "Scene.hpp"
#include <iostream>
CameraMovementCallback::CameraMovementCallback(camera_ptr cam)
{	
	_cam = cam;
	_angularVelocity = 0.01;
	_speed = 0.1;
}

CameraMovementCallback::~CameraMovementCallback()
{

}

void CameraMovementCallback::execute()
{
	getKeyState();
}

// Reads the keystate from the keyState singleton class
// and updates the camera
void CameraMovementCallback::getKeyState()
{	

	KeyState::State st = KeyState::getInstance().get();
	if( st & key_state_bit::KEY_W) 
	{
		_cam->translate(Vec3(0,0,_speed));
	}
	if( st & key_state_bit::KEY_A)
	{
		_cam->rotate(_angularVelocity, Vec3(0,1,0));
	}
	if( st & key_state_bit::KEY_S )
	{
		_cam->translate(Vec3(0,0,-_speed));
	}
	if( st & key_state_bit::KEY_D )
	{
		_cam->rotate(-_angularVelocity, Vec3(0,1,0));
	}
	if( st & key_state_bit::KEY_P)
	{
		_cam->setPerspectiveProjection();
		//std::cout << _cam->getViewMat() << std::endl<<std::endl;
		//std::cout << _cam->getPos() << std::endl << std::endl;
	}
	if( st & key_state_bit::KEY_O)
	{
		_cam->setOrthographicProjection();
	}
	if( st & key_state_bit::KEY_Z )
	{
		_cam->translate(Vec3(0,-_speed,0));

	}
	if( st & key_state_bit::KEY_X )
	{
		_cam->translate(Vec3(0,_speed,0));

	}
	if( st & key_state_bit::KEY_R)
	{
		_cam->lookAt(Vec3(0,0,4), Vec3(0,0,0), Vec3(0,1,0));
		_cam->setPerspectiveProjection();
	}
	if( st & key_state_bit::KEY_T)
	{
		_cam->lookAt(Vec3(0,5,4), Vec3(0,0,0), Vec3(0,1,0));
		_cam->setPerspectiveProjection();
		//_cam->setOrthographicProjection();
	}

}
