#ifndef CAMERA_MOVEMENT_CALLBACK_HPP
#define CAMERA_MOVEMENT_CALLBACK_HPP
#include "Camera.hpp"
#include "KeyState.hpp"

class CameraMovementCallback : public UpdateCallback
{
	public:
		CameraMovementCallback(camera_ptr cam);
		virtual ~CameraMovementCallback();

		void execute();

		void getKeyState();

		void updateCamera();
	private:
		camera_ptr _cam;

		
};

#endif //CAMERA_MOVEMENT_CALLBACK_HPP
