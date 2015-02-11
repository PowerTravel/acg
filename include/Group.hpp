#ifndef GROUP_HPP
#define GROUP_HPP

#include "Node.hpp"
#include <list>

class NodeVisitor;

#ifndef NODE_LIST
#define NODE_LIST
typedef std::list< std::shared_ptr<Node> > NodeList;
#endif // NODE_LIST

class Group: public Node{

	public:
		Group();
		virtual	~Group();
		
		void addChild( std::shared_ptr<Node> nodePtr);
		void destroy();
		void update();
		
		void accept(NodeVisitor& v);
		

		int getNrChildren();
		
		NodeList childList;
	private:
};
#endif // GROUP_HPP
