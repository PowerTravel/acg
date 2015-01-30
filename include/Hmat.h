#ifndef HMAT_H
#define HMAT_H
#include <iostream>
#include <vector>
#include "Hvec.h"

class Hmat
{
	// Input  /  Output streams
	friend std::istream& operator>>(std::istream& is, Hmat& hm);
	friend std::ostream& operator<<(std::ostream& os,const Hmat& hm);

	// Matrix-Matrix Adition, Subtraction and multiplication;	
	friend Hmat operator+(Hmat& h1, Hmat& h2);
	friend Hmat operator-(Hmat& h1, Hmat& h2);
	friend Hmat operator*(Hmat& h1, Hmat& h2);
	
	// Vector-Matrix multiplication
	friend Hvec operator*(Hvec& v, Hmat& m);
	friend Hvec operator*(Hmat& m, Hvec& v);

	// Scalar-Matrix multiplication
	friend Hmat operator*(float& f, Hmat& hm);
	friend Hmat operator*(Hmat& hm, float& f);

	public:
		// What type of norm one wants.
		enum NormFlag
		{
			P1,
			INF,
		};
		// How the matrix should be initialized upon creation.
		enum TypeFlag
		{
			IDENTITY,
			ZERO
		};

		// Constructor / Destructors
		Hmat(TypeFlag = IDENTITY);
		Hmat(float mat[]);
		Hmat(Hvec r0, Hvec r1, Hvec r2, Hvec r3);
		virtual ~Hmat();

		// Subscript
		Hvec& operator[](int idx);
		const Hvec& operator[](int idx) const;
		// Equality
		bool operator==(const Hmat& hm);	
		bool operator!=(const Hmat& hm);

		// Matrix-Matrix aggregate Adition, Subtraction and multiplication;
		Hmat& operator+=(Hmat& hm);
		Hmat& operator-=(Hmat& hm);
		Hmat& operator*=(Hmat& hm);

		// Scalar-Matrix aggregate multiplication
		Hmat& operator*=(float& f);

		float getVal(int idx); // Get a value using single int, row oriented
		Hmat T(); 			// Get a transposed matrix
		Hvec row(int idx);	// Get a row vector
		Hvec col(int idx);	// Get a column vector 
		float norm(NormFlag type=INF);
		Hmat inv(); // Not implemented, returns inverse; Should return null matrix on failure
	private:
		std::vector<Hvec> m;
};

#endif // HMAT_H
