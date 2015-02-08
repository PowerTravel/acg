#include "Transform.hpp"
#include <cstdio>

Transform::Transform()
{
	m = Hmat();
	pos = Vec4();
}

Transform::~Transform()
{

}

void Transform::update()
{
}
