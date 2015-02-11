#ifndef RENDER_VISITOR_HPP
#define RENDER_VISITOR_HPP

#include "NodeVisitor.hpp"

class RenderVisitor : public NodeVisitor{

	public:
		RenderVisitor();
		virtual ~RenderVisitor();
	
		void apply(Geometry* g);
		void apply(Group* grp);
		void apply(Transform* t);
};



#endif // RENDER_VISITOR_HPP
