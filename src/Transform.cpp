#include "Transform.hpp"
#include "Hmat.hpp"
#include "NodeVisitor.hpp"
#include "Quaternion.hpp"
#include <cstdio>

Transform::Transform()
{
	_r = Quaternion();
	_p = Vec3();
	_s = Vec3(1,1,1);
}

Transform::Transform(float angle, Vec3 axis, Vec3 position, Vec3 scale)
{
	_r = Quaternion(angle, axis);
	_p = position;
	_s = scale;
}

Transform::~Transform()
{

}

Hmat Transform::getModelMatrix()
{
	Hmat T,R,S,ANS;
	T = getTransMat();

	if(_r.zeroRotation()){
		R = Hmat();
	}else{
		R = getRotMat();
	}
	R = getRotMat();
	S = getScaleMat();

	ANS = R * S;
	ANS = T * ANS;

//std::cout<< ANS << std::endl<<std::endl;
	return ANS; 
}

void Transform::setPos(Vec3 p)
{
	_p = p;
}
void Transform::setScale(Vec3 s)
{
	_s = s;
}
void Transform::setOrientation(float angle, Vec3 axis)
{
	_r.set(angle,axis);
}

Hmat Transform::getTransMat( )
{
	return generateTransMat(_p);
}
Hmat Transform::getRotMat( )
{
	return _r.asHmat();
}
Hmat Transform::getScaleMat( )
{
	return generateScaleMat(_s);
}

void Transform::translate(Vec3 ds)
{
	 _p = _p+ds;
}

void Transform::rotate(float angle, Vec3 axis)
{
	Quaternion q;
	q.makeRotate(angle, axis);
	_r = _r*q;
}

void Transform::rotate(Vec3 to)
{
//	Vec3 from;
//	float angle;
//	_r.getRotate(angle, from);
//	Quaternion q;
//	q.makeRotate(angle, from);
//	_r = _r*q;
}

void Transform::scale(Vec3 ds)
{
	_s[0] = _s[0]*ds[0];
	_s[1] = _s[1]*ds[1];
	_s[2] = _s[2]*ds[2];
}

Hmat Transform::generateTransMat( Vec3 ds )
{
	Vec4 v1 = Vec4(1.0f, 0.0f, 0.0f, ds[0]);
	Vec4 v2 = Vec4(0.0f, 1.0f, 0.0f, ds[1]);
	Vec4 v3 = Vec4(0.0f, 0.0f, 1.0f, ds[2]);
	Vec4 v4 = Vec4(0.0f, 0.0f, 0.0f, 1.0f);

	return Hmat(v1,v2,v3,v4);
}


Hmat Transform::generateRotMat(float angle, Vec3 axis )
{
	Quaternion q = Quaternion(angle,axis);
	return q.asHmat();
}

Hmat Transform::generateScaleMat( Vec3 ds )
{
	Vec4 v1 = Vec4(ds[0], 0.0f, 0.0f, 0.0f);
	Vec4 v2 = Vec4(0.0f, ds[1], 0.0f, 0.0f);
	Vec4 v3 = Vec4(0.0f, 0.0f, ds[2], 0.0f);
	Vec4 v4 = Vec4(0.0f, 0.0f, 0.0f, 1.0f);
	return Hmat(v1,v2,v3,v4);
}


void Transform::update()
{
	Vec3 v = Vec3(0.0, 1.0, 0.0);
	rotate(0.001, v);
}


void Transform::accept(NodeVisitor& visitor)
{
	visitor.apply(this);
}
