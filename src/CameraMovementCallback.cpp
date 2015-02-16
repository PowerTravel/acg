#include "CameraMovementCallback.hpp"
#include <iostream>
#include "Scene.hpp"
#include <iostream>
CameraMovementCallback::CameraMovementCallback(camera_ptr cam)
{	
	_cam = cam;
}

CameraMovementCallback::~CameraMovementCallback()
{

}

void CameraMovementCallback::execute()
{
	getKeyState();

	updateCamera();
}

void CameraMovementCallback::getKeyState()
{	

	KeyState::State st = KeyState::getInstance().get();


	if( st & key_state_bit::KEY_W) 
	{
		std::cerr << " forward! ";	
	}
	if( st & key_state_bit::KEY_A)
	{
		std::cerr << " left! ";	
	}
	if( st & key_state_bit::KEY_S )
	{
		std::cerr << " back! ";	
	}
	if( st & key_state_bit::KEY_D )
	{
		std::cerr << " right! ";	
	}
	if( st & (	key_state_bit::KEY_W |
				key_state_bit::KEY_A |
				key_state_bit::KEY_S |	
				key_state_bit::KEY_D))
	{
		std::cerr<< std::endl;
	}
}

void CameraMovementCallback::updateCamera()
{

}
