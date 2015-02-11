#ifndef TRANSFORM_HPP
#define TRANSOFRM_HPP

#include "Group.hpp"
#include "Quaternion.hpp"
#include "Vec3.hpp"
class NodeVisitor;
class Hmat;

class Transform: public Group
{
	public:
		Transform();
		Transform(float angle, Vec3 axis, Vec3 position, Vec3 scale);
		virtual ~Transform();

		void update();

		void accept(NodeVisitor& visitor);

		// Getters
		Hmat getModelMatrix();
		Hmat getTransMat();
		Hmat getRotMat();
		Hmat getScaleMat();

		// Setters
		void setPos(Vec3 p);
		void setScale(Vec3 s);
		void setOrientation(float angle, Vec3 axis);


		// Manipulate
		void translate(Vec3 ds);
		void rotate(float angle, Vec3 axis);
		void rotate(Vec3 to);
		void scale(Vec3 ds);

		// Utility
		static Hmat generateTransMat( Vec3 ds );
		static Hmat generateRotMat(float angle, Vec3 axis );
		static Hmat generateScaleMat( Vec3 ds );

	private:
		Quaternion _r; // Rotation
		Vec3 _s; // Scaling
		Vec3 _p; // Position

		
};

#endif // TRANSFORM_HPP
