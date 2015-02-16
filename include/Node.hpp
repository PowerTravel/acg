#ifndef NODE_HPP
#define NODE_HPP

#include <memory>
#include "State.hpp"
#include "UpdateCallback.hpp"


class NodeVisitor;

//#ifndef STATE_PTR
//#define STATE_PTR
//typedef std::shared_ptr<State> state_ptr;
//#endif // STATE_PTR

//#ifndef CALLBACK_PTR
//#define CALLBACK_PTR
//typedef std::shared_ptr<UpdateCallback> callback_ptr;
//#endif // CALLBACK_PTR

#ifndef NODE_PTR
#define NODE_PTR
class Node;
typedef std::shared_ptr<Node> node_ptr;
#endif // NODE_PTR

class Node{


	public:
		
		enum Type{NODE, GROUP};
	
		Node();
		virtual ~Node();

		virtual void update();

		virtual void acceptVisitor(class NodeVisitor& v) =  0;
		virtual void connectCallback(callback_ptr cb);
		UpdateCallback* getUpdateCallback();

		Type getType();
		void setState(state_ptr s);
		state_ptr getState();	


	protected:
		Type _type;
		state_ptr _state;
		callback_ptr _callback;


};


#endif //NODE_HPP
