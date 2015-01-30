#include "Vec4.hpp"
//#include "Hmat.h"
#include <cmath>
#include <stdexcept>
Vec4::Vec4()
{
	v[0]=0.0;
	v[1]=0.0;
	v[2]=0.0;
	v[3]=0.0;
}

Vec4::Vec4(float x, float y, float z, float w)
{
	v[0]=x;
	v[1]=y;
	v[2]=z;
	v[3]=w;
}

Vec4::~Vec4()
{

}


// read
std::istream& operator>>(std::istream& is, Vec4& v4)
{
	is >> v4.v[0] >> v4.v[1] >> v4.v[2] >> v4.v[3];
	
	// initialize a default Vec4 if is is bad
	if(!is){ v4 = Vec4(); }

	return is;
}

// write
std::ostream& operator<<(std::ostream& os, const Vec4& v4)
{
	os << v4[0] << " " << v4[1] << " " << v4[2] << " " << v4[3]; 
	return os;
}

// Dot product
float operator*( Vec4 v1, Vec4 v2 )
{
	float x,y,z,w;
	x = v1.v[0] * v2.v[0];
	y = v1.v[1] * v2.v[1];
	z = v1.v[2] * v2.v[2];
	w = v1.v[3] * v2.v[3];
	return x+y+z+w;
}

// vector adition
Vec4 operator+(Vec4& v1, Vec4& v2)
{
	float x,y,z,w;
	x=v1.v[0]+v2.v[0];
	y=v1.v[1]+v2.v[1];
	z=v1.v[2]+v2.v[2];
	w=v1.v[3]+v2.v[3];
	return Vec4(x,y,z,w);
}

// Vector subtraction
Vec4 operator-(Vec4& v1, Vec4& v2)
{
	float x,y,z,w;
	x=v1.v[0]-v2.v[0];
	y=v1.v[1]-v2.v[1];
	z=v1.v[2]-v2.v[2];
	w=v1.v[3]-v2.v[3];
	return Vec4(x,y,z,w);
}

// Scalar-Vector Multiplication
Vec4 operator*(float& f, Vec4& v4)
{
	// For some reason this function cant access the private member v
	float x,y,z,w;
	x = f*v4[0];
	y = f*v4[1];
	z = f*v4[2];
	w = f*v4[3];
	return Vec4(x,y,z,w);
}

// Scalar-Vector Multiplication
Vec4 operator*(Vec4& v4, float f)
{
	return f*v4;
}

// Subscript
float& Vec4::operator[](int idx)
{
	if( (idx<0) || (idx>3) ){
		throw std::out_of_range("index out of range");
	}
	return v[idx];
}

// Const Subscript
const float& Vec4::operator[](int idx) const
{
	if( (idx<0) || (idx>3) ){
		throw std::out_of_range("index out of range");
	}
	return v[idx];
}

// Equal to
bool Vec4::operator==( const Vec4& v4 )
{
	if( (v[0]==v4[0]) && (v[1]==v4[1]) && (v[2]==v4[2]) && (v[3]==v4[3]) )
	{
		return true;
	}else{
		return false;
	}
}


// Not equal to
bool Vec4::operator!=( const Vec4& v4 )
{
	return !( *this == v4 );
}


// L0, L1, L2 and INF norm
float Vec4::norm(NormType type)
{
	float ans=0;
	switch(type)
	{
		case L0:
		{
			float j=0;
			for (int i = 0; i<4; i++)
			{
				if(v[i] != 0)
				{
					j++;
				}
			}
			ans = j;
			break;
		}
		case L1:
		{
			ans = abs(v[0])+abs(v[1])+abs(v[2])+abs(v[3]);
			break;
		}
		case L2:
		{
			ans = sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]+v[3]*v[3]);
			break;
		}
		case INF:
		{
			float val1  = abs(v[0]);
			for(int i=1; i<4; i++)
			{	
				float val2 = abs(v[i]);
				if(val1 < val2)
				{
					val1 = val2;
				}
			}
			ans = val1;
			break;
		}
		default:
		{
			ans = 0;
			break;
		}
	}
	return ans;
}


// Compound vector Adition
Vec4& Vec4::operator+=( Vec4& v4 )
{	
	*this = *this + v4;
	return *this;
}

// Compound Vector subtraction
Vec4& Vec4::operator-=( Vec4& v4 )
{
	*this = *this - v4;
	return *this;
}


// Compound scalar vector multiplication
Vec4& Vec4::operator*=( float& f )
{
	*this = *this * f;
	return *this;
}
















