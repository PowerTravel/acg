#ifndef TRANSFORM_HPP
#define TRANSOFRM_HPP

#include "Group.hpp"
#include "TransformMatrix.hpp"

class NodeVisitor;
class Hmat;
class Vec3;

class Transform: public Group
{
	public:
		Transform();
		virtual ~Transform();

		Hmat getM();
		void setM(Hmat m);

		void rotate(float angle, Vec3 axis);
		void scale(Vec3 ds);
		void translate(Vec3 ds);

		void update();
		void accept(NodeVisitor& visitor);

	private:
		TransformMatrix _T;
		
};

#endif // TRANSFORM_HPP
