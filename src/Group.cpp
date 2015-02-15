#include "Group.hpp"
#include "NodeVisitor.hpp"
#include <cstdio>
Group::Group()
{
	_type = Node::GROUP;
	childList = std::list<std::shared_ptr<Node> >();
}

Group::~Group()
{
	destroy();
}

void Group::destroy()
{
	while(!childList.empty())
	{
		childList.pop_back();
	}
}

void Group::addChild(std::shared_ptr<Node> nodePtr )
{
	childList.push_back(nodePtr);
}

int Group::getNrChildren()
{
	return childList.size();
}

void Group::update()
{
	for(NodeList::const_iterator ci = childList.begin(); ci != childList.end(); ci++ )
	{
		Node* node_ptr = ci->get();
		node_ptr->update();
	}
}

void Group::accept(NodeVisitor& v)
{	
	v.apply(this);
}
