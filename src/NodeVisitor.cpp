#include "NodeVisitor.hpp"

#include "Geometry.hpp"
#include "Group.hpp"
#include "Transform.hpp"

NodeVisitor::NodeVisitor()
{
}
NodeVisitor::~NodeVisitor(){}

void NodeVisitor::traverse(Node* node)
{
	if(node->getType() ==  Node::GROUP  )
	{
		Group* grpPtr =(Group*) node;
		NodeList childList = grpPtr->childList;
		int i = 1;
		node->acceptVisitor(*this);
		for(NodeList::const_iterator ci = childList.begin(); ci != childList.end(); ci++)
		{
			//printf("Entering child no %d \n", i);	
			traverse(*ci);
			i++;
		}
	}else{
	//	printf("Entering leaf \n");	
		node->acceptVisitor(*this);
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
void NodeVisitor::apply(Transform* t)
{
	printf("Visiting Transform from NodeVisitor \n");
}
void NodeVisitor::apply(Camera* cam)
{
	printf("Visiting Camera from NodeVisitor \n");
}
