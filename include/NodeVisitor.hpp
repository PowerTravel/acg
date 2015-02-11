#ifndef NODEVISITOR_HPP
#define NODEVISITOR_HPP

#include <memory>
#include "State.hpp"
#include "Node.hpp"

class Node;
class Geometry;
class Group;
class Transform;


class NodeVisitor{

	public:

		NodeVisitor();
		virtual ~NodeVisitor();
	
		virtual void traverse( Node* node );

		virtual void apply(Geometry* g);
		virtual void apply(Group* grp);
		virtual void apply(Transform* t);

	private:
};


#endif // NODEVISITOR_HPP
