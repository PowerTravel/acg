#include "NodeVisitor.hpp"

#include "Geometry.hpp"
#include "Group.hpp"
#include "Transform.hpp"

NodeVisitor::NodeVisitor(){}
NodeVisitor::~NodeVisitor(){}

void NodeVisitor::traverse(Node* node)
{
	if(node->getType() ==  Node::GROUP  )
	{
		Group* grpPtr =(Group*) node;
		NodeList childList = grpPtr->childList;
		for(NodeList::const_iterator ci = childList.begin(); ci != childList.end(); ci++)
		{
	//		printf("This is a Group, JUMP \n");
			node->accept(*this);
			traverse(ci->get());
		
		}
	}else{
	//	printf("This is a Leaf, STOP \n");
		Geometry* geomPtr = (Geometry*) node;
		node->accept(*this);
	}
}


// Update the _state untill we get to a leaf and update();
void NodeVisitor::apply(Geometry* g)
{
	printf("Visiting Geometry from NodeVisitor \n");
}
void NodeVisitor::apply(Group* grp)
{
	printf("Visiting Group from NodeVisitor\n");
}
void NodeVisitor::apply(Transform* trans)
{
	printf("Visiting Transform from NodeVisitor \n");
}
