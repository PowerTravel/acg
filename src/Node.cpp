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

/*
 * Name:	Update
 * Purpose: Updates the aspects of the node if it has a callback
 * Input:	-
 * Output:	-
 * Misc:	-
 */
void Node::update()
{
	if( _callback!= NULL){
		_callback->execute();
	}
}

/*
 * Name:	connectCallback
 * Purpose:	Connects a callback to the node.
 * Input:	std::shared_ptr<UpdateCallback>: The callback base class.
 * Output:	-
 * Misc:	-
 */
void Node::connectCallback(callback_ptr cb)
{
	_callback = cb;
}

/*
 * Name:	getUpdateCallback
 * Purpose:	returns a pointer to the attached callback
 * Input:	-
 * Output:	UpdateCallbacl*: A pointer to the attached Callback
 * Misc:	Return NULL if there is no callback attached.
 */
UpdateCallback* Node::getUpdateCallback()
{
	return _callback.get();
}

/*
 * Name:	setState
 * Purpose:	Updates the state of the Node
 * Input:	State* s: A pointer to the state
 * Output:	-
 * Misc:	The state is not copied over to the NODE.
 *			it is merged with the existing state of the NODE.
 *			The node will retain all of its previous set state-
 *			-attributes and take on the new ones of the new state.
 *			Can be called multiple times to accumulate state 
 *			attributes.
 */
void Node::setState(State* s)
{
	if(s != NULL){
		_state->merge(s);
	}
}

/*
 * Name: 	getState
 * Purpose:	Returns a pointer to the state of the NODE for direct
 *			manipulation.
 * Input:	-
 * Output:	State*: A pointer to the nodes state.
 * Misc:	-
 */
State* Node::getState()
{
	return _state.get();
}

/*
 * Name:	getType
 * Purpose:	gets the Type of the node, which tells us if it is able
 *			to have children or not.
 * Input: 	-
 * Output:	Node::Type: the type of the node.
 * Misc:	Type can be 'NODE' or 'GROUP' The difference between them
 * 			being that GROUP can have children while NODE cannot.
 *			It is set at creation and cannot be changed later.
 */
Node::Type Node::getType()
{
	return _type;
}
