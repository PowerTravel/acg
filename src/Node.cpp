#include "Node.hpp"
#include "NodeVisitor.hpp"
Node::Node()
{
	state = NULL;
	_type = NODE;
	_state = CLOSED;
}

Node::~Node()
{
	state = NULL;
}

void Node::update()
{

}


Node::VisitedState Node::isOpened()
{
	return _state;
}

void Node::open()
{
	_state = OPEN;
}

void Node::close()
{
	_state = VISITED;
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
