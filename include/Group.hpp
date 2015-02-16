#ifndef GROUP_HPP
#define GROUP_HPP

#include "Node.hpp"
#include <list>

class NodeVisitor;

#ifndef NODE_LIST
#define NODE_LIST
typedef std::list< std::shared_ptr<Node> > NodeList;
#endif // NODE_LIST

#ifndef GROUP_PTR
#define GROUP_PTR
class Group;
typedef std::shared_ptr<Group> group_ptr;
#endif // GROUP_PTR

class Group: public Node{

	public:
		Group();
		virtual	~Group();
		
		void addChild( std::shared_ptr<Node> nodePtr);
		void destroy();
		void update();
		
		void acceptVisitor(NodeVisitor& v);
		

		int getNrChildren();
		
		NodeList childList;
	private:
};
#endif // GROUP_HPP
