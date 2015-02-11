#include "Node.hpp"
#include "NodeVisitor.hpp"
Node::Node()
{
	state = NULL;
	_type = NODE;
}

Node::~Node()
{
	state = NULL;
}

void Node::update()
{

}

void Node::setState(std::shared_ptr<State> s)
{
	state = s;
}

std::shared_ptr<State> Node::getState()
{
	return state;
}

Node::Type Node::getType()
{
	return _type;
}
