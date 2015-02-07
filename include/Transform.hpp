#ifndef TRANSFORM_HPP
#define TRANSOFRM_HPP

#include "Group.hpp"

class Transform: public Group
{
	public:
		Transform();
		virtual ~Transform();

		void update();
};

#endif // TRANSFORM_HPP
