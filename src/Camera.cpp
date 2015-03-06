#include "GL/glew.h"
#include "Camera.hpp"
#include "NodeVisitor.hpp"
#include <cmath>
Camera::Camera()
{
	_V.set(Hmat());
	_P = Hmat();
	setPerspectiveProjection();
}

Camera::Camera(Vec3 eye, Vec3 at, Vec3 up)
{
	lookAt(eye,at,up);
	_P = Hmat();
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
 * Purpose: Rotates the camera to point at 'at'v 
 * Input:	Vec3 at: A point which the camera should look at.
 * Output:	-	
 * Misc:	-
 */
void Camera::lookAt(Vec3 at)
{
	// Extract the 'up' or y-axis and the position
	// from the view matrix and update the viewMatrix
	Hmat M = _V.get();
	Vec3 vy = Vec3(M[1][0], M[1][1], M[1][2]);
	Vec3 pos = Vec3(M[0][3], M[1][3], M[2][3]);
	lookAt(pos, at, vy);
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
	Vec3 vz = at-eye;
	vz.normalize();
	Vec3 vx = up^vz; // ^ means cross-product
	vx.normalize();
	Vec3 vy = vz^vx;
	vy.normalize();

	// Build a rotationmatrix which rotates from world coordinates
	// to camera coordinates
	float tx,ty,tz;
	float tx1 = -(eye*vx);
	float ty2 = -(eye*vy);
	float tz3 = -(eye*vz);
	tx = - eye[0]*vx[0] - eye[1]*vx[1] - eye[2]*vx[2]; 
	ty = - eye[0]*vy[0] - eye[1]*vy[1] - eye[2]*vy[2]; 
	tz = - eye[0]*vz[0] - eye[1]*vz[1] - eye[2]*vz[2];

	float m[] = {	vx[0], vx[1], vx[2], tx, 
					vy[0], vy[1], vy[2], ty, 
					vz[0], vz[1], vz[2], tz,
					0.0f ,0.0f, 0.0f, 1};
	Hmat V = Hmat(m);
	_V.set(V);
}

/*
 * Name:	translate
 * Purpose: Translates the camera by 't'.
 * Input:	-Vec3 t: A vector containing the ammount and direction 
 *			of the translation.
 * Output:	-
 * Misc:	It translates by t, not to t.
 */
void Camera::translate(Vec3 t)
{
	_V.translate(t);
}

/*
 * Name:	rotateAroundOrigin
 * Purpose: Rotates the camera around world-origin.
 * Input:	-float angle: The angle of rotation
 * Output:	-Vec3 axis: The axis of rotation
 * Misc:	-Uses a dirty hack
 */
void Camera::rotateAroundOrigin(float angle, Vec3 axis)
{	
	// Rotates around the origin because we only rotate the
	// view-matrix directly. Quite a dirty hackind of a hack 
	// since the cameras position never changes.
	_V.rotate(angle,axis);
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
	setAspect(); // Get the active aspect ratio from GLUT
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

    GLint portSize[4];
  	glGetIntegerv(GL_VIEWPORT, portSize);
	float w2 = (float) portSize[2]-portSize[0];
	float scale = w/w2;
	float h2 = (float) portSize[3]-portSize[1];

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

void Camera::setAspect()
{
    GLint portSize[4];
    glGetIntegerv( GL_VIEWPORT, portSize );
	float w = (float) portSize[2]-portSize[0];
	float h = (float) portSize[3]-portSize[1];
	_aspect = w/h;
}
