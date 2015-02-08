#ifndef TRANSFORM_HPP
#define TRANSOFRM_HPP

#include "Group.hpp"

class Transform: public Group
{
	public:
		Transform();
		virtual ~Transform();

		void setPosition(Vec3 pos);

		void update();

	private:
		Hmat m;
		Vec4 pos;
};

#endif // TRANSFORM_HPP
