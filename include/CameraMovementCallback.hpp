#ifndef CAMERA_MOVEMENT_CALLBACK_HPP
#define CAMERA_MOVEMENT_CALLBACK_HPP
#include "Camera.hpp"

class CameraMovementCallback : public UpdateCallback
{
	public:
		CameraMovementCallback(camera_ptr cam)

		void execute();
	private:
		camera_ptr _cam;
}

#endif //CAMERA_MOVEMENT_CALLBACK_HPP
