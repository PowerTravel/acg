#include "Transform.hpp"
#include "NodeVisitor.hpp"
#include <cstdio>

Transform::Transform()
{
}

Transform::~Transform()
{

}


void Transform::update()
{
}



void Transform::accept(NodeVisitor& visitor)
{
	visitor.apply(this);
}
