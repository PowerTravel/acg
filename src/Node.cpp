#include "Node.hpp"
#include "NodeVisitor.hpp"
Node::Node()
{
	_state = NULL;
	_type = NODE;
}

Node::~Node()
{
	_state = NULL;
	_callback = NULL;
}

void Node::update()
{
}

void Node::connectCallback(callback_ptr cb)
{
	_callback = cb;
}

UpdateCallback* Node::getUpdateCallback()
{
	return _callback.get();
}

void Node::setState(std::shared_ptr<State> s)
{
	_state = s;
}

std::shared_ptr<State> Node::getState()
{
	return _state;
}

Node::Type Node::getType()
{
	return _type;
}
