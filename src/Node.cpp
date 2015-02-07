#include "Node.hpp"

Node::Node()
{
	state = std::shared_ptr<State>();
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

/*
void Node::accept(Visitor* v)
{
	v->apply(this);
}
*/
