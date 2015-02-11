#ifndef RENDER_VISITOR_HPP
#define RENDER_VISITOR_HPP

#include "NodeVisitor.hpp"
#include "Hmat.hpp"
#include <list>


class RenderVisitor : public NodeVisitor{

	public:

		RenderVisitor();
		virtual ~RenderVisitor();
		
		void apply(Geometry* g);
		void apply(Group* grp);
		void apply(Transform* t);

	private:

		struct Mc{
			Hmat m; 
			int count;
		};
		
		std::list<Mc> mList; // Model List
		std::list<Mc> vList; // View list
	

		void decrease_mList();
};



#endif // RENDER_VISITOR_HPP
