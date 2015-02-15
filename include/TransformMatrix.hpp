#ifndef TRANSFORM_MATRIX_HPP
#define TRANSFORM_MATRIX_HPP
#include "Hmat.hpp"

class Vec3;

class TransformMatrix{

	public:
		TransformMatrix();
		virtual ~TransformMatrix();

		void rotate(float angle, Vec3 axis);
		void scale(Vec3 sacle);
		void translate(Vec3 trans);

		Hmat get();
		void set(Hmat m);

	private:
		Hmat _m;
};

#endif //TRANSFORM_MATRIX_HPP
