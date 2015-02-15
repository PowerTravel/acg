#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "Group.hpp"
#include "Hmat.hpp"
#include "TransformMatrix.hpp"
class Camera : public Group
{

	public:
		Camera();
		virtual ~Camera();

		void accept(NodeVisitor& v);

		void perspective(float fovy, float aspect, float near, float far);
		void orthographic( float left, float right, float bottom,
				    float top,  float near,  float far);
		void lookAt(Vec3 v);
		void lookAt(Vec3 eye, Vec3 at, Vec3 up);
		Hmat getProjectionMat();
		Hmat getViewMat();
	private:
		Hmat _P; // Projection
		TransformMatrix _V;
		float fovy,aspect,near,far;
		float _width;
		float _height;
};

#endif // CAMERA_HPP
