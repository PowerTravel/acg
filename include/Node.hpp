#ifndef NODE_HPP
#define NODE_HPP

#include <memory>
#include "State.hpp"


class NodeVisitor;

class Node{

	public:
		
		enum Type{NODE, GROUP};
	
		Node();
		virtual ~Node();

		virtual void update();

		virtual void accept(class NodeVisitor& v) =  0;

		Type getType();
		void setState(std::shared_ptr<State> s);
		std::shared_ptr<State> getState();	
	protected:
		Type _type;
		std::shared_ptr<State> state;

};

#endif //NODE_HPP
