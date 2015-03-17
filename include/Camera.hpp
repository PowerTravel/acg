#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "Group.hpp"
#include "Hmat.hpp"
#include "TransformMatrix.hpp"

#ifndef CAMERA_PTR
#define CAMRA_PTR
class Camera;
typedef std::shared_ptr<Camera> camera_ptr;
#endif //CAMERA_PTR

/*
 *	Class: 		Camera
 *	Purpose: 	A camera.
 *	Misc:		Derived from group.
 */
class Camera : public Group
{

	public:
		Camera();
		Camera(Vec3 eye, Vec3 at, Vec3 up);
		virtual ~Camera();

		// Take a visitor
		void acceptVisitor(NodeVisitor& v);

		// Manipulation of position and orientation
		void lookAt(Vec3 v);
		void lookAt(Vec3 eye, Vec3 at, Vec3 up);
		void rotateAroundOrigin(float angle, Vec3 axis);
		void translate(Vec3 t);

		// Getters of the view and projection matrices
		Hmat getProjectionMat();
		Hmat getViewMat();

		// Support is given for perspective and orthographic projection
		void setPerspectiveProjection(float fovy=45.f, float near=-1.f, float far=-30.f);
		void setOrthographicProjection(float left=-10.f, float right=10.f, float bottom=-10.f, float top=10.f, float near = 50.f, float far =-50.f );

		void setAspect(float aspect);
	private:
		



		Hmat _P; // Projection matrix
		TransformMatrix _V; // View matrix

		// Variables related to perspective projection
		float _fovy, _aspect, _near, _far;
		// Variables related to position and orientation
		Vec3 _eye, _at, _up;
	
		// The actual implementation of perspective and orthographic projection
		void perspective();
		void orthographic( float left, float right, float bottom,
				    float top,  float near,  float far);
};

#endif // CAMERA_HPP
