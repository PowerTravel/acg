#include "Transform.hpp"
#include "Hmat.hpp"
#include "NodeVisitor.hpp"
#include "Vec3.hpp"
#include <cstdio>

Transform::Transform()
{
	 _T=TransformMatrix();
}

Transform::~Transform()
{

}

Hmat Transform::getM()
{
	return _T.get().T(); 
}

void Transform::setM(Hmat m)
{
	_T.set(m); 
}

void Transform::translate(Vec3 ds)
{
	_T.translate(ds);
}

void Transform::rotate(float angle, Vec3 axis)
{
	_T.rotate(angle, axis);
}

void Transform::scale(Vec3 ds)
{
	_T.scale(ds);
}

void Transform::update()
{
	Vec3 v1 = Vec3(0.0, 0.0, 1.0);
	Vec3 v2 = Vec3(-0.05, 0.00, 0.00);
	Vec3 v3 = Vec3(1.0, 1.0, 1.00);
	rotate(0.05, v1);
//	translate(v2);
//	scale(v3);
}


void Transform::accept(NodeVisitor& visitor)
{
	visitor.apply(this);
}
