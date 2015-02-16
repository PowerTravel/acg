#include "TransformSpinCallback.hpp"
#include "Transform.hpp"
#include <cstdio>
TransformSpinCallback::TransformSpinCallback(transform_ptr t)
{
	_t = t;
}

TransformSpinCallback::~TransformSpinCallback()
{

}

void TransformSpinCallback::execute()
{
	Vec3 v = Vec3(0,0,-1);
	float angle = 0.01;
	_t->rotate(angle, v);
}
