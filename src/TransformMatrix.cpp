#include "TransformMatrix.hpp"
#include "Quaternion.hpp"
#include "Vec3.hpp"

TransformMatrix::TransformMatrix()
{
	_m = Hmat();
}

TransformMatrix::~TransformMatrix()
{

}

void TransformMatrix::rotate(float angle, Vec3 axis)
{
	// tto = translate TO origin,
	// tfo = translate (back) FROM origin;
	Vec3 tto = Vec3( -_m[0][3], -_m[1][3], -_m[2][3] );
	Vec3 tfo = Vec3( _m[0][3], _m[1][3], _m[2][3] );
	translate(tto);

	Quaternion q = Quaternion(angle,axis);
	Hmat R = q.asHmat();

	_m = R*_m;

	translate(tfo);
}

void TransformMatrix::scale(Vec3 scale)
{
	Hmat S = Hmat();
	for(int i=0; i<3; i++)
	{
		S[i][i] = scale[i];
	}
	_m = S*_m;
}

void TransformMatrix::translate(Vec3 trans)
{
	Hmat T = Hmat();
	T[0][3]=trans[0]; 
	T[1][3]=trans[1];
	T[2][3]=trans[2];
	T[3][3]= 1;
	_m= T*_m;
}

// OPENGL IS USES COLUMN MAJOR REPRESENTATION 
// OF MATRICES.
Hmat TransformMatrix::get()
{
	return _m;
}

void TransformMatrix::set(Hmat m)
{
	_m =m;
}
