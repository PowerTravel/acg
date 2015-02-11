#ifndef QUATERNION_HPP
#define QUATERNION_HPP

#include "Vec4.hpp"
#include "Vec3.hpp"
class Quaternion{

	public:
		Quaternion();
		Quaternion(float x, float y, float z, float w);
		virtual ~Quaternion();

		void set( Vec3& from, Vec3& to);
		void set(float x, float y, float z, float w);
		void set(Vec4 vec);
		void set(float angle, Vec3 axis);
		void makeRotate(float angle, Vec3 vec);
		void makeRotate(float angle, float x, float y, float z);
		void makeRotate(const Vec3 from, const Vec3 to);
		void getRotate(float& angle, Vec3& v);
		void getRotate(float& angle, float& x, float& y, float& z );
		void slerp(float t, Quaternion& from, Quaternion& to);
		Quaternion negative();
		Vec4 asVec4();

	private:
		Vec4 _v;	
};

#endif // QUATERNION
