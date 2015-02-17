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
		void apply(Camera* t);

		void printMatStruct();
	
	private:
	
		struct Mc{
			Hmat m; 
			int count;

		};
		typedef std::list<Mc>::iterator listIt;	
		typedef std::list<Mc>::const_iterator constListIt;	
		std::list<Mc> mList; // Model List
	
		void decrease_mList();
		void push_mList(int count, Hmat m);
		void modify_mList(int count, Hmat m);
		void updateState(State* st);
};

#endif // RENDER_VISITOR_HPP
