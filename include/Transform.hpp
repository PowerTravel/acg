#ifndef TRANSFORM_HPP
#define TRANSOFRM_HPP

#include "Group.hpp"
class NodeVisitor;

class Transform: public Group
{
	public:
		Transform();
		virtual ~Transform();

		void update();

		void accept(NodeVisitor& visitor);

	private:
};

#endif // TRANSFORM_HPP
