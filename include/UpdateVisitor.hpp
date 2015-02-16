#ifndef UPDATE_VISITOR_HPP
#define UPDATE_VISITOR_HPP

#include "NodeVisitor.hpp"

class UpdateVisitor : public NodeVisitor{
	
	public:	
		UpdateVisitor();
		virtual ~UpdateVisitor();

		void apply(Geometry* g);
		void apply(Group* grp);
		void apply(Transform* t);
		void apply(Camera* cam);

};


#endif // UPDATE_VISITOR_HPP
