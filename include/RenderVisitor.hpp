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
		struct Sc{
			state_ptr s; 
			int count;

		};
		typedef std::list<Mc>::iterator listIt;	
		typedef std::list<Mc>::const_iterator constListIt;	
		std::list<Mc> mList; // Model List	
		std::list<Sc> sList; // State List

		float _M[16]; // Model Mat
		float _V[16];
		float _P[16];
		bool _isModelviewSet;
		// DET ÄR NÅGOT SKUMT MED MODELMAT. Om jag deklarerar
		// deklarerar Hmat MODELVIEW; här och i apply(geometry)
		// anropar MODELVIEW = mList.front().m så får jag segfault
		// Om jag deklarerar en lokal Hmat i apply(geometry) så
		// får jag segfault när jag stänger av programmet.
//		Hmat _V; // View Mat
//		Hmat _P; // Projection Mat

		void decrease_mList();
		void modify_mList(int count, Hmat m);

		void decrease_sList();
		void push_sList(int count, State* s);
		void makeStateCurrent(State* s);
		state_ptr syncStates(State* lastState, State* newState);
};

#endif // RENDER_VISITOR_HPP
