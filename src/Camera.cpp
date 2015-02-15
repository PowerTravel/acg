#include "GL/glew.h"
#include "Camera.hpp"
#include "NodeVisitor.hpp"
#include <cmath>
Camera::Camera()
{
	//aspect = 1;
	lookAt(Vec3(0.f,0.f,-3.f), Vec3(0.f,0.f,0.f), Vec3(0.f,1.f,0.f));
	aspect = 4.f/3.f;
	fovy = 110;
	near = -1;
	far = -600;
	perspective(fovy, aspect, near, far);
	//orthographic(-4, 4, -2, 2, -4, 4);
}
/*
void Camera::perspective(float fovy, float aspect, float near, float far)
{
	_P = Hmat();

    //GLint portSize[4];
    //glGetIntegerv( GL_VIEWPORT, portSize );
	//float w = (float) portSize[2]-portSize[0];
	//float h = (float) portSize[3]-portSize[1];
	//float asp = w/h;
	

	float top = near*tan((fovy/2)*(3.1418/180));
	float right = top * aspect;
	_P[0][0] = near/right;
	_P[1][1] = near/top;
	_P[2][2] = (-far+near)/(far-near);
	_P[3][3] = 0.f;
	_P[2][3] = -1.f;
	_P[3][2] = -2*(far*near)/(far-near);

//	float top = near*tan( (fovy/2)*(PI/180) );
//	float right = top * aspect;
//	aspectRatio = aspect;
//	
//	Vector4::iMat(P);
//	P[IMAT16(0,0)] = near/right;
//	P[IMAT16(1,1)] = near/top;	
//	P[IMAT16(2,2)] = (-far+near)/(far-near);
//	P[IMAT16(3,3)] = 0.f;	
//	P[IMAT16(2,3)] = (-2*far*near)/(far-near);
//	P[IMAT16(3,2)] = -1.f;

}
	*/

void Camera::perspective(float fovy, float aspect, float near, float far)
{
	_P = Hmat();

    GLint portSize[4];
    glGetIntegerv( GL_VIEWPORT, portSize );
	float w = (float) portSize[2]-portSize[0];
	float h = (float) portSize[3]-portSize[1];
	float asp = w/h;
	

/*
	float A = 1/(tan((fovy/2.f)*(3.1418/180)) *w/h);
	float B = 1/tan((fovy/2.f)*(3.1418/180));
	_P[0][0] = A;
	_P[1][1] = B;
	_P[2][2] = far/(far-near);
	_P[3][3] = 0.f;
	_P[3][2] = -1.f;
	_P[2][3] = -(far*near)/(far-near);
*/


	float top = near*tan( (fovy/2)*(3.1418/180.f) );
	float right = top * aspect;
	
	_P[0][0] = near/right;
	_P[1][1] = near/top;	
	_P[2][2] = (-far+near)/(far-near);
	_P[3][3] = 0.f;	
	_P[2][3] = (-2*far*near)/(far-near);
	_P[3][2] = -1.f;

	
}

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
	h = h2*scale;

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
//	_P = ortho;
}

Camera::~Camera()
{

}

Hmat Camera::getProjectionMat()
{
	std::cout << "T" << std::endl;
	std::cout << _P.T() << std::endl;
	return _P.T();
}

Hmat Camera::getViewMat()
{
	std::cout << "V" << std::endl;
	std::cout << _V.get().T() << std::endl;
	return _V.get().T();
}

void Camera::accept(NodeVisitor& v)
{
	v.apply(this);
}

void Camera::lookAt(Vec3 at)
{
	//Vec3 vx = Vec3(P[0][0], P[0][1], P[0][2]);
	Vec3 vy = Vec3(_P[1][0], _P[1][1], _P[1][2]);
	//Vec3 vz = Vec3(P[2][0], P[2][1], P[2][2]);
	Vec3 pos = Vec3(_P[0][3], _P[1][3], _P[2][3]);

	lookAt(pos, at, vy);
}

void Camera::lookAt(Vec3 eye, Vec3 at, Vec3 up)
{
/*
	Vec3 camRef = eye - at;
	camRef.normalize();

	Vec3 camV = up^camRef;
	camV.normalize();

	Vec3 camUp = camRef^camV;
	camUp.normalize();
	
	// The translation matrix
	// It is negative since we want to translate the camera from camPos down to the origin.
//	Vector4::getTransMat(-camPos[0],-camPos[1],-camPos[2],T);
//	Vector4::mult(M,T,V);

	// This is our inverted=(transposed) RotationMatrix.
	// Same as with T, we want to rotate the camera (back) to be 
	// oriented with the world.
	
	Hmat M = Hmat();
	M[0][0] = camV[0];
	M[0][1] = camV[1];
	M[0][2] = camV[2];
	M[1][0] = camUp[0];
	M[1][1] = camUp[1];
	M[1][2] = camUp[2];
	M[2][0] = camRef[0];
	M[2][1] = camRef[1];
	M[2][2] = camRef[2];
	_V.set(M);
	*/

	Vec3 vz = at-eye;
	vz.normalize();
	Vec3 vx = up^vz;
	vx.normalize();
	Vec3 vy = vz^vx;
	vy.normalize();
	
	float tx,ty,tz;
	float tx1 = -(eye*vx);
	float ty2 = -(eye*vy);
	float tz3 = -(eye*vz);
	tx = - eye[0]*vx[0] - eye[1]*vx[1] - eye[2]*vx[2]; 
	ty = - eye[0]*vy[0] - eye[1]*vy[1] - eye[2]*vy[2]; 
	tz = - eye[0]*vz[0] - eye[1]*vz[1] - eye[2]*vz[2];

	std::cout << "eye: " <<eye << std::endl;
	std::cout << "vz: "<<vz << std::endl;
	Vec3 trans = Vec3(tx1,ty2,tz3);
	std::cout << "trans: "<<trans<<std::endl;
	

	float m[] = {	vx[0], vx[1], vx[2], tx, 
					vy[0], vy[1], vy[2], ty, 
					vz[0], vz[1], vz[2], tz,
					0.0f ,0.0f, 0.0f, 1};
	Hmat V = Hmat(m);
	_V.set(V.T());

}

/*
void update()
{
	_width;
	_height;
    GLint portSize[4];
  	glGetIntegerv(GL_VIEWPORT, portSize);
	float new_width = (float) portSize[2]-portSize[0];
	float scale =screen_width/w2;
	float new_height = (float) portSize[3]-portSize[1];
	
	screen_height = new_height * scale;
}
*/
