#ifndef NODEVISITOR_HPP
#define NODEVISITOR_HPP

#include <memory>
#include "State.hpp"
#include "Node.hpp"
#include <list>

class Node;
class Geometry;
class Group;
class Transform;
class Camera;

#ifndef NODE_LIST
#define NODE_LIST
typedef std::list< Node* > NodeList;
#endif //NODE_LIST

class NodeVisitor{

	public:

		NodeVisitor();
		virtual ~NodeVisitor();
	
		virtual void traverse( Node* node );

		virtual void apply(Geometry* g);
		virtual void apply(Group* grp);
		virtual void apply(Transform* t);
		virtual void apply(Camera* cam);

};


#endif // NODEVISITOR_HPP
