#include "CameraMovementCallback.hpp"
#include <iostream>
#include "Scene.hpp"
#include <iostream>
CameraMovementCallback::CameraMovementCallback(camera_ptr cam)
{	
	_cam = cam;
	_p = Vec3();
	_move = Vec3();
	_speed = 0.05;
	_update = false;
}

CameraMovementCallback::~CameraMovementCallback()
{

}

void CameraMovementCallback::execute()
{
	getKeyState();
	
	if(_update)
	{
		updateCamera();
	}
}

void CameraMovementCallback::getKeyState()
{	

	KeyState::State st = KeyState::getInstance().get();

	//_move = Vec3();
//	_update = false;
	if( st & key_state_bit::KEY_W) 
	{
		//std::cerr << " up ";
		//_move[1] = _speed;
		_cam->rotateAround(_speed, Vec3(1,0,0), Vec3(0,0,0));
	}
	if( st & key_state_bit::KEY_A)
	{
		//std::cerr << " left ";
		//_move[0] = -_speed;
		_cam->rotateAround(-_speed, Vec3(0,1,0), Vec3(0,0,0));
	}
	if( st & key_state_bit::KEY_S )
	{
		//std::cerr << " down ";	
		//_move[1] = -_speed;
		_cam->rotateAround(-_speed, Vec3(1,0,0), Vec3(0,0,0));
	}
	if( st & key_state_bit::KEY_D )
	{
//		std::cerr << " right ";	
		//_move[0] = _speed;
		_cam->rotateAround(_speed, Vec3(0,1,0), Vec3(0,0,0));

	}
	if( st & (	key_state_bit::KEY_W |
				key_state_bit::KEY_A |
				key_state_bit::KEY_S |	
				key_state_bit::KEY_D))
	{
	//	_update = true;
	//	std::cerr<< std::endl;
	}
}

void CameraMovementCallback::updateCamera()
{
	//_cam->rotateAround(_speed, Vec3(0,1,0), Vec3(0,0,0));
}
