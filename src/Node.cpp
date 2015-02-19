#include "Node.hpp"
#include "NodeVisitor.hpp"
Node::Node()
{
	_state = NULL;
	_type = NODE;
}

Node::~Node()
{
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

void Node::setState(state_ptr s)
{
	_state = s;
}

state_ptr Node::getState()
{
	return _state;
}

Node::Type Node::getType()
{
	return _type;
}
