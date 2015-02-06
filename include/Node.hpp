#ifndef NODE_HPP
#define NODE_HPP

#include "DList.hpp"
class Node{

	public:
		Node();
		virtual ~Node();
		
		void addChild( Node* node);

		virtual void update();

		void destroy();

		void release();

	protected:
		Dlist< Node* > childList;
	private:
		

}

#endif //NODE_HPP
