#include "Node.hpp"
#include "NodeVisitor.hpp"
Node::Node()
{
	_state = std::shared_ptr< State >(new State());
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

void Node::setState(State* s)
{
	if(s != NULL){
		_state->merge(s);
	}
}

State* Node::getState()
{
	return _state.get();
}

Node::Type Node::getType()
{
	return _type;
}
