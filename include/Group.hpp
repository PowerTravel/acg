#ifndef GROUP_HPP
#define GROUP_HPP

#include "Node.hpp"
#include "DList.hpp"

class Group: public Node{

	public:
		Group();
		virtual	~Group();
		
		void addChild( std::shared_ptr<Node> node);
		void destroy();
	private:
		DList<Node> childList;
};
#endif // GROUP_HPP
