#ifndef RENDER_VISITOR_HPP
#define RENDER_VISITOR_HPP

#include "NodeVisitor.hpp"
#include "Hmat.hpp"
#include <list>

class RenderToTexture;


/*	
 *	Class: 		RenderVisitor
 *	Purpose: 	Traverses the scenegraph and renders it.
 *	Misc:		Derived from nodeVisitor. This is quite a 
 *				complex class that does very different things
 *				depending on which node it is visiting
 *				and the different nodes interact with eachother.
 */
class RenderVisitor : public NodeVisitor{

	public:

		RenderVisitor();
		virtual ~RenderVisitor();
		
		void apply(RenderToTexture* tex);
		void apply(Geometry* g);
		void apply(Group* grp);
		void apply(Transform* t);
		void apply(Camera* t);

		//void printMatStruct();
	
	private:
		// The struct that adds transformation matrices	
		struct Mc{
			Hmat m; 	// The composite model matrix
			int count;  // The number of unvisited children
		};
		// The struct that adds states together
		struct Sc{
			state_ptr s; // The composite state 
			int count;   // The number of unvusuted Children

		};

		typedef std::list<Mc>::iterator listIt;	
		typedef std::list<Mc>::const_iterator constListIt;	
		// The mList is a list of composite model matrices.
		// Each entry in the model matrix is the product of the
		// total model matrices above it in the tree.
		// So when we reach a leaf, the first entry  in the
		// mList is the product of all model matrices above it.
		// These lists are reffered to aggregate lists
		std::list<Mc> mList; // Model List

		// This list functions the same way as mList but sums
		// States instead of matrices.
		std::list<Sc> sList; // State List

		// Using vectors since Hmat is acting weird, see below
		float _M[16]; // Model matrix
		float _V[16]; // View matrix
		float _P[16]; // Projection matrix
		bool _isModelviewSet;
		
		// DET ÄR NÅGOT SKUMT MED MODELMAT. Om jag deklarerar
		// deklarerar Hmat MODELVIEW; här och i apply(geometry)
		// anropar MODELVIEW = mList.front().m så får jag segfault
		// Om jag deklarerar en lokal Hmat i apply(geometry) så
		// får jag segfault när jag stänger av programmet.
//		Hmat _V; // View Mat
//		Hmat _P; // Projection Mat


		RenderToTexture* _rtt;

		// Methods related to manipulating the mList
		void decrease_mList();
		void modify_mList(int count, Hmat m);

		// Methods related to manipulating sList	
		void decrease_sList();
		void modify_sList(int count, State* s);
		void makeStateCurrent(State* s);
		state_ptr syncStates(State* lastState, State* newState);
};

#endif // RENDER_VISITOR_HPP
