#ifndef NODE_HPP
#define NODE_HPP

#include <memory>
#include "State.hpp"

//#include "Visitor"

class Node{

	public:
		Node();
		virtual ~Node();

		virtual void update();

		//void accept(Visitor* v);

		void setState(std::shared_ptr<State> s);
		std::shared_ptr<State> getState();	
	protected:
		std::shared_ptr<State> state;

};

#endif //NODE_HPP
