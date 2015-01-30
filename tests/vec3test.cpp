#include "Vec3.hpp"
#include <iostream>
#include <sstream>
#include <cmath>
using namespace std;

bool testSubscript();
bool testEquality();
bool testAdd();
bool testSub();
bool testDot();
bool testScalMult();
bool testNorm();

int	main(int argc, const char* argv[])
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
	if( !testDot() )
	{
		cout << "Failed 5" << endl;
		return 5;
	}
	if( !testScalMult() )
	{
		cout << "Failed 6" << endl;
		return 6;
	}
	if( !testNorm() )
	{
		cout << "Failed 7" << endl;
		return 7;
	}
	
	cout << "Test went ok" << endl;
	return 0;
}

bool testSubscript()
{
	Vec3 v1 = Vec3(1.0, 2.0, 3.0);
	Vec3 v2 = v1;
	v1[0] = v2[2];
	v1[2] = -1.0;
	if( !((v1[0]==3.0) && (v1[1] == 2.0) && (v1[2]== -1.0) ) )
	{
		return false;
	}
	if(!((v2[0]==1.0) && (v2[1] == 2.0) && (v2[2]== 3.0) ) ){
		return false;
	}
	return true;
}
bool testEquality()
{
	Vec3 v1 = Vec3(1.0, 2.0, 3.0);
	Vec3 v2 = Vec3(1.0, 2.0, 3.0);
	Vec3 v3 = Vec3(1.0, 2.0, -2.0);
	if( !(v1 == v2) || !(v2 != v3) )
	{
		return false;
	}

	return true;
}

bool testAdd()
{
	Vec3 v1 = Vec3(3.0, 2.0, 1.0);
	Vec3 v2 = Vec3(1.0, 2.0, 3.0);
	Vec3 ans = Vec3(4.0,4.0,4.0);
	Vec3 v3 = v1 + v2;
	v1 += v2;
	if( (v1 != v3) || (v3 != ans) || (v1 == v2)  )
	{
		return false;
	}
	return true;
}

bool testSub()
{
	Vec3 v1 = Vec3(3.0, 2.0, 1.0);
	Vec3 v2 = Vec3(1.0, 2.0, 3.0);
	Vec3 ans = Vec3( 2.0, 0.0, -2.0);
	Vec3 v3 = v1 - v2;
	v1 -= v2;
	if( (v1 != v3) || (v3 != ans) || (v1 == v2)  )
	{
		return false;
	}
	return true;
}

bool testDot()
{
	Vec3 v1 = Vec3(3.0, 2.0, 1.0);
	Vec3 v2 = Vec3(1.0, 2.0, 3.0);
	float dotProd = v1 * v2;
	float ans = 10;
	if( dotProd != ans)
	{
		return false;
	}
	return true;
}

bool testScalMult()
{
	Vec3 v1 = Vec3(1.0,2.0,3.0);
	Vec3 v2 = Vec3(2.0, 3.0, 4.0);
	Vec3 ans1 = Vec3(10.0, 20.0, 30.0);
	Vec3 ans2 = Vec3(20.0, 30.0, 40.0);
	Vec3 ans3 = Vec3(200.0, 300.0, 400.0);
	float scal = 10;


	v1 = scal * v1;
	v2 = v2 * scal;

	if( (v1!=ans1) || (v2!=ans2) )
	{
		cout << "lol" << endl;
		return false;
	}
	
	v2 *= scal;
	if( v2 != ans3 )
	{
		cout << "lel" << endl;
		return false;
	}

	return true;
}

bool testNorm()
{
	Vec3 v = Vec3(0.0,3.0,4.0);
	float l0 = v.norm(Vec3::L0);
	float l1 = v.norm(Vec3::L1);
	float l2 = v.norm();
	float inf = v.norm(Vec3::INF);

	if( (l0 != 2) || (l1 != 7.0) || ((l2 - sqrt(9+16))>0.00001) || (inf != 4) )
	{
		return false;
	}

	return true;
}
