#include "GL/glew.h"
#include "Camera.hpp"
#include "NodeVisitor.hpp"
#include <cmath>
Camera::Camera()
{
	_V.set(Hmat());
	_P = Hmat();
	_R = Hmat();
	_pos = Vec3(-2,0,0); 
	_x = Vec3(1,0,0);
	_y = Vec3(0,1,0);
	_z = Vec3(0,0,1);

	_moved = true;
	_perspectiveChange = true;

	_aspect =1;
	setPerspectiveProjection();
}

Camera::Camera(Vec3 eye, Vec3 at, Vec3 up)
{
	lookAt(eye,at,up);
	_P = Hmat();
	_aspect =1;
	setPerspectiveProjection();
}

Camera::~Camera()
{

}

/*
 * Name:	acceptVisitor
 * Purpose: Takes a visitor
 * Input:	NodeVisitor& v: A reference to a nodevisitor
 * Output:	-
 * Misc:	-
 */
void Camera::acceptVisitor(NodeVisitor& v)
{
	v.apply(this);
}

/*
 * Name:	lookAt
 * Purpose: Translates the camera to 'eye', points it at 'at' and
 *			rotates it so that 'up' is up.
 * Input:	Vec3 eye: The position of the camera
 *			Vec3 at: The look-at point
 *			Vec3 up: The up-vector.
 * Output:	
 * Misc:	
 */
void Camera::lookAt(Vec3 eye, Vec3 at, Vec3 up)
{
	// Calculate the x, y and z axis for the camera.
	_pos = eye;
	_z = at-_pos;
	_z.normalize();
	_x = up^_z; // ^ means cross-product
	_x.normalize();
	_y = _z^_x;
	_y.normalize();
	_moved = true;
}

void Camera::translate(Vec3 t)
{
	Vec4 T = Vec4(t[0], t[1], t[2]);
	Hmat V_inv = _V.getRigidInverse();
	Vec3 dt = (V_inv*T).asVec3();
	_pos = _pos + dt;
	_moved = true;
}

void Camera::rotate(float angle, Vec3 axis)
{	
	TransformMatrix R = TransformMatrix();
	R.rotate(angle,axis);
	Hmat HR = R.get();

	_R = HR*_R;	

	Vec4 xc = _R.row(0);
	Vec4 yc = _R.row(1);
	Vec4 zc = _R.row(2);
  
	Hmat V_inv = _V.getRigidInverse();
	_x = (V_inv*xc).asVec3(); 
	_y = (V_inv*yc).asVec3();
	_z = (V_inv*zc).asVec3();
	
	_moved = true;
}

/*
 * Name:	setPerspectiveProjection	
 * Purpose: Creates a perspective projection
 * Input:	float fovy: The field of view
 *			float near: The near clipping plane
 *			float far: 	The far clipping plane
 * Output:	-	
 * Misc:	Breaks dependance rules by using a GLUT function.
 *			Want to change it at a later point (probably never)
 *			Actual implementation is in the function perspective()
 *			further down.
 */
void Camera::setPerspectiveProjection(float fovy, float near, float far)
{
	_fovy = fovy;
	_near = near;
	_far = far;
	perspective();
}

/*
 * Name:	setOrthographicProjection	
 * Purpose: creates an orthographic projection
 * Input:	float left: The left clipping plane
 *			float right: The right clipping plane
 *			float bottom: The bottom clipping plane
 *			float top: The top clipping plane
 *			float near: The near clipping plane
 *			float far: The far clipping plane
 * Output:	-
 * Misc:	Actual implementation is in the function 
 *			orthographic(float, float, float, float, float, float) 
 *			further down.
 */
void Camera::setOrthographicProjection(float left, float right, float bottom, float top, float near, float far)
{
	orthographic(left, right, bottom, top, near, far);
}


// The implementation of the perspective projection
void Camera::perspective()
{
	_P = Hmat();

	float top = _near*tan( (_fovy/2)*(3.1418/180.f) );
	float right = top * _aspect;
	
	_P[0][0] = _near/right;
	_P[1][1] = _near/top;	
	_P[2][2] = (-_far+_near)/(_far-_near);
	_P[3][3] = 0.f;	
	_P[2][3] = (-2*_far*_near)/(_far-_near);
	_P[3][2] = -1.f;
}


// The implementation of the orthographic projection
void Camera::orthographic(	float left, float right, float bottom,
							float top, float near, float far)
{
	float w = (int) (right - left);
	float h = (int) (top - bottom);

	float d = (int) (far - near);
	float asp = (w/h);

	Hmat ortho = Hmat();

	ortho[0][0] = 2/w;
	ortho[1][1] = 2/h;
	ortho[2][2] = -2/d;
//	ortho[2][2] = 0;
	ortho[0][3] = -(right+left)/(right-left);
	ortho[1][3] = -(top+bottom)/(top-bottom);
	ortho[2][3] = (far+near)/(far-near);

	Hmat mOrth = Hmat();
	mOrth[2][2] = 0.f;
	_P = ortho * mOrth;
}

Hmat Camera::getProjectionMat()
{
	return _P.T();
}

Hmat Camera::getViewMat()
{
	return _V.get();
}

Vec3 Camera::getPos()
{
	return _pos;
}

void Camera::setAspect(float aspect)
{
	_aspect = aspect;
}

void Camera::update()
{
	if( _callback!= NULL){
		_callback->execute();
	}
	
	if( _moved )
	{
		updatePosition();
		_moved = false;
		_R = Hmat();
	}
}

void Camera::updatePosition()
{
	float tx,ty,tz;
	tx = - _pos[0]*_x[0] - _pos[1]*_x[1] - _pos[2]*_x[2]; 
	ty = - _pos[0]*_y[0] - _pos[1]*_y[1] - _pos[2]*_y[2]; 
	tz = - _pos[0]*_z[0] - _pos[1]*_z[1] - _pos[2]*_z[2];

	float v[] = {	_x[0], _x[1], _x[2], tx, 
					_y[0], _y[1], _y[2], ty, 
					_z[0], _z[1], _z[2], tz,
					0.0f ,0.0f, 0.0f, 1};
	Hmat V = Hmat(v);
	_V.set(V);
}
