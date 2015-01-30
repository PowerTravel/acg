#include <iostream>
#include <cmath>
#include "Hmat.h"
using namespace std;

bool testSubscript();
bool testEquality();
bool testAdd();
bool testSub();
bool testVecMult();
bool testScalMult();
bool testTranspose();
bool testRowCol();
bool testNorm();
bool testInv();

int main()
{
	if( !testSubscript() )
	{
		cout << "Failed 1" << endl;
		return 1;
	}
	if( !testEquality() )
	{
		cout << "Failed 2" << endl;
		return 2;
	}
	if( !testAdd() )
	{
		cout << "Failed 3" << endl;
		return 3;
	}
	if( !testSub() )
	{
		cout << "Failed 4" << endl;
		return 4;
	}
	if( !testVecMult() )
	{
		cout << "Failed 5" << endl;
		return 5;
	}
	if( !testScalMult() )
	{
		cout << "Failed 6" << endl;
		return 6;
	}
	if( !testTranspose() )
	{
		cout << "Failed 7" << endl;
		return 7;
	}
	if( !testRowCol() )
	{
		cout << "Failed 8" << endl;
		return 8;
	}

	if( !testNorm() )
	{
		cout << "Failed 9" << endl;
		return 9;
	}

	if( !testInv() )
	{
		cout << "Failed 10" << endl;
		return 10;
	}

	cout << "Test went ok" << endl;
	return 0;
}

bool testSubscript()
{
	Hmat m1 = Hmat();
	Hmat m2 = m1;	
	float f[16] = {1,2,3,4,   5,6,7,8,   9,10,11,12,   13,14,15,16};
	Hmat ref = Hmat(f);

	for(int i = 0; i < 4; i++) 
	{
		for (int j = 0; j < 4; j++) {
			m1[i][j] = ref[i][j];
		}
		m2[i] = ref[i];	
	}

	for(int i = 0; i < 4; i++) 
	{
		for (int j = 0; j < 4; j++) {
			if( m1[i][j] != ref[i][j] )
			{
				return false;
			}
		}
		if ( m2[i] != ref[i] )
		{
			return false;
		}
	}

	return true;
}

bool testEquality()
{
	Hvec r1,r2,r3,r4;
	r1 = Hvec(1,2,3,4);
	r2 = Hvec(5,6,7,8);
	r3 = Hvec(9,10,11,12);
	r4 = Hvec(13,14,15,16);
	Hmat ref = Hmat(r1,r2,r3,r4);
	Hmat m = ref;

	if(m != ref)
	{
		return false;
	}
	
	if( !(m == ref) )
	{
		return false;
	}

	for(int i = 0; i < 4; i++) 
	{
		for (int j = 0; j < 4; j++) {
			m = ref;
			m[i][j] = 0;
			if( m == ref )
			{
				return false;
			}
			if( !(m != ref) )
			{
				return false;
			}
		}
	}	

	return true;
}

bool testAdd()
{
	float f1[16] = {1,2,3,4,   5,6,7,8,   9,10,11,12,   13,14,15,16};
	float f2[16] = {2,2,3,4,   5,7,7,8,   9,10,12,12,   13,14,15,17};
	Hmat m1 = Hmat();
	Hmat m2 = Hmat(f1);
	Hmat ans = Hmat(f2);

	Hmat m3 = m1+m2;
	m1 += m2;

	if( (m1 != ans) || (m3 != ans)  )
	{
		return false;
	}

	return true;
}

bool testSub()
{
	float f1[16] = {1,2,3,4,   5,6,7,8,   9,10,11,12,   13,14,15,16};
	float f2[16] = {0,-2,-3,-4,   -5,-5,-7,-8,   -9,-10,-10,-12,   -13,-14,-15,-15};
	
	Hmat m1 = Hmat();
	Hmat m2 = Hmat(f1);
	Hmat ans = Hmat(f2);

	Hmat m3 = m1-m2;
	m1 -= m2;

	if( (m1 != ans) || (m3 != ans)  )
	{
		return false;
	}

	return true;
}

bool testVecMult()
{
	float f1[16] = {-10,8,-8,5,   6,4,1,-4,   8,-1,6,4,   8,4,-2,-2};
	float f2[16] = {-8,3,5,10,   3,2,-8,10,   -7,2,5,-9,   0,8,2,10};
	float f3[16] = {160, 10,-144,102,   -43, -4, -5, 51,  -109, 66, 86, 56,   -38, 12, -6, 118};

	Hmat m0m1 = Hmat();
	Hmat m0m2 = Hmat(f1);
	Hmat m0Prod = m0m1*m0m2;
	Hmat m0Agg = m0m1;
	m0Agg *= m0m2;
	Hmat m0Ans = Hmat(f1);


	Hmat m1m1 = Hmat(f1);
	Hmat m1m2 = Hmat(f2);
	Hmat m1Prod = m1m1*m1m2;
	Hmat m1Agg = m1m1;
	m1Agg *= m1m2;
	Hmat m1Ans = Hmat(f3);

	if( (m0Prod != m0Ans) || (m0Agg != m0Ans) || (m1Prod != m1Ans) || (m1Agg != m1Ans)  )
	{
		return false;
	}

	return true;
}


bool testScalMult()
{
	float scal = 2;
	float f[16] = {-1,0,2,4,   1,2,3,4,   -1,-2,-3,-4,   4,3,2,0};	
	float ansf[16] = {-2,0,4,8,   2,4,6,8,   -2,-4,-6,-8,   8,6,4,0};	
	
	Hmat m = Hmat(f);
	Hmat ans = Hmat(ansf);
	
	Hmat result1 = m * scal;
	Hmat result2 = scal * m;
	Hmat result3 = m;
	result3 *= scal;

	if( (result1 != ans) || (result2 != ans) || (result3 != ans) )
	{
		return false;
	}
	return true;
}


bool testTranspose()
{	
	float f[16] = {-1,0,2,4,   1,2,3,4,   -1,-2,-3,-4,   4,3,2,0};	
	float ft[16] = {-1,1,-1,4,  0,2,-2,3,  2,3,-3,2,  4,4,-4,0};

	Hmat m1 = Hmat(f);
	Hmat m1t;

	Hmat m2 = Hmat(ft);
	Hmat m2t;

	// For some reason the operator cant take the return of m.T().
	//if( ( m != mt.T() ) || (mt != m.t() ) )
	if( ( m1 != (m2t=m2.T()) ) || (m2 != (m1t=m1.T()) ) )
	{
		return false;
	}

	return true;
}

bool testRowCol()
{	
	float f[16] = {-1,0,2,4,   1,2,3,4,   -1,-2,-3,-4,   4,3,2,0};
	Hmat m1 = Hmat(f);
	Hmat m2 = m1.T();

	for(int i = 0; i<4; i++)
	{
		if( m1.row(i) != m2.col(i) )
		{
			return false;
		}
	}

	return true;

}

bool testNorm()
{
	float f[16] = {-10,8,-8,5,   6,4,1,-4,   8,-1,6,4,   8,4,-2,-2};
	Hmat m = Hmat(f);
	float normP1 = 32;
	float normINF = 31;

	if( (m.norm(Hmat::P1) != normP1) || (m.norm(Hmat::INF) != normINF) )
	{	
		return false;	
	}

	return true;
}

bool testInv()
{
	float f[16] = {1,0,0,1,  1,1,1,4,  -3,2,1,4,  0,1,3,3};
	Hmat m=Hmat(f);
	float finv[16] = {-9,5,-2,-1,  -36,18,-6,-4,  1,-1,0,1,  11,-5,2,1};
	for (int i = 0; i < 16; i++) {
		finv[i] = finv[i]/2.0;
	}
	Hmat mAns = Hmat(finv);

	Hmat mInv = m.inv();

	float diffP1 = abs(mAns.norm(Hmat::P1) - mInv.norm(Hmat::P1));
	float diffINF = abs(mAns.norm(Hmat::INF) - mInv.norm(Hmat::INF));
	float tol = 0.00001;
	
	if( (diffP1 > tol) || (diffINF > tol) )
	{
		return false;
	}

	return true;
}
