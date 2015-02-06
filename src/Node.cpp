#include "Node.hpp"

void Node::Node()
{
	childList = Dlist< Node* >();
}

void Node::~Node()
{
	destroy();
}

void Node::destroy()
{
	childList.first();
	while(!childList.isEmpty())
	{
		std::weak_ptr<Node> w_child = childList.inspect();
		if(!w_child.expired())
		{
			std::shared_ptr<Node> s_child = child.lock();
			s_child->destroy();
		}
		childList.remove();
	}
}

void Node::release(){}

void Node::update(){}
