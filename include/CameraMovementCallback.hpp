#ifndef CAMERA_MOVEMENT_CALLBACK_HPP
#define CAMERA_MOVEMENT_CALLBACK_HPP
#include "Camera.hpp"
#include "KeyState.hpp"


// Rotates the camera around the point _p at constant distance
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
		Vec3 _p;
		Vec3 _move;
		float _speed;
		bool _update;
		
};

#endif //CAMERA_MOVEMENT_CALLBACK_HPP
