#include "CameraMovementCallback.hpp"

CameraMovementCallback::CameraMovementCallback(caera_ptr cam)
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
