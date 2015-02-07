#include "Group.hpp"

Group::Group()
{
	childList = DList<Node>();
}

Group::~Group()
{
	destroy();
}

void Group::destroy()
{
	childList.first();
	while(!childList.isEmpty())
	{
		childList.remove();
	}
}

void Group::addChild(std::shared_ptr<Node> node )
{
	childList.insert(node);
}

/*
void Group::update()
{
	childList.first();
	while(!childList().isEnd())
	{
		std::shared_ptr<Node> node_ptr = childList.inspect().lock();
		node_ptr->update();
		childList.next();
	}
}
*/	

