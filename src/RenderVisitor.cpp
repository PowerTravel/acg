#include <GL/glew.h>
#include "RenderVisitor.hpp"
#include "RenderToTexture.hpp"
#include "Transform.hpp"
#include "Geometry.hpp"
#include "Camera.hpp"
#include <iostream>
#include "Scene.hpp"


RenderVisitor::RenderVisitor()
{
	mList =std::list<Mc>();
	sList = std::list<Sc>();
	_isModelviewSet = false;
	_rtt = NULL;
}

RenderVisitor::~RenderVisitor()
{

}

void RenderVisitor::apply(RenderToTexture* tex)
{
	modify_mList(tex->childList.size(), Hmat());
	modify_sList(tex->childList.size(), tex->getState());

	//State s = State();
	//s.addTexture(State::SHADOW, tex->getTexture());
}



/*
 * Name:	apply (Geometry)
 * Purpose: Renders a geometry with the accumulated transformation
 *			matrix and the accumulated state.
 * Input:	Geometry* g: The geometry that is to be rendered
 * Output:	-	
 * Misc:	-
 */
void RenderVisitor::apply(Geometry* g)
{
	// this matrix contain the accumulated ModelMatrix.
	mList.front().m.get(_M); 
	
	// We sync the geometries state with the lates entry in the sList.
	state_ptr state = syncStates(sList.front().s.get(),g->getState() );

	if( state->isShaderSet() )
	{
		// If a material is set previously it overrides
		// any material that may have been loaded to the 
		// geometry from a file.
		if(sList.front().s->isMaterialSet())
		{
			state->setMaterial(sList.front().s->getMaterial());
		}

		// Apply the state to openGL
		state->apply();

		// Send the Model View and projection matrices to the shader
		shader_ptr shader = state->getShader();		
		shader->setUniformMatrix("M",1, _M);
		if(_isModelviewSet)
		{
			shader->setUniformMatrix("V", 1, _V);
			shader->setUniformMatrix("P", 1, _P);
		}else{
			std::cerr<<"No CameraMatrix active. Probably not rendering properly."<<std::endl;
		}

		// draw the geometry
		g->draw();
	}else{
		std::cerr<<"No shader present. Not rendering geometry."<<std::endl;
	}

	// Since we are in a leaf we now want to erase all entries
	// in these lists up to the entry that has unvisited children.
	decrease_sList();
	decrease_mList();
}

/*
 * Name:	Apply (Group)	
 * Purpose: Add entries to the aggregate lists. 
 * Input:	Group* grp: The group to be visited
 * Output:	-
 * Misc:	-
 */
void RenderVisitor::apply(Group* grp)
{
	// This node will never have transformation matrices,
	// But it may have children, thus we add a unit matrix
	// together with the number of children it has.
	modify_mList(grp->childList.size(), Hmat());

	// We also sync the states and add them to the sList
	modify_sList(grp->childList.size(), grp->getState());
}

/*
 * Name:	apply (Camera)
 * Purpose: Adds entries to the aggregate lists
 * Input:	Camera* cam: The camera to be visited
 * Output:	-	
 * Misc:	Assumes we only have one camera. The latest camera
 *			is the only one that will be rendered.
 */
void RenderVisitor::apply(Camera* cam)
{
	// We save the View and Projection Matrices
	cam->getViewMat().get(_V);
	cam->getProjectionMat().get(_P);
	_isModelviewSet = true;

	// See apply (Group)
	modify_mList(cam->childList.size(), Hmat());
	modify_sList(cam->childList.size(), cam->getState());
}


/*
 * Name:	apply (Transform)	
 * Purpose:	adds its transformationMatrix to the mList as well as
 *			its state.
 * Input:	Transform* t: The transformation node to be visited.	
 * Output:	-	
 * Misc:	-
 */
void RenderVisitor::apply(Transform* t)
{	
	modify_mList(t->childList.size(), t->getM());
	modify_sList(t->childList.size(), t->getState());
}

/*
 * Name:	modify_mList	
 * Purpose: Adds or removes entries in the mList
 * Input:	-int count: The number of children the added Hmat
 *			will be relevant for.
 *			-Hnat m: The matrix to be summed up.
 * Output:	-
 * Misc:	-
 */
 // Use for group nodes
void RenderVisitor::modify_mList(int count, Hmat m)
{
	// If the node is a leaf
	if(count == 0)
	{	
		// If we are in a leaf we have to popp all entries
		// that corresponds to already visited nodes with
		// no children. Those entries are the ones where 
		// 'count' has been reduced to 1; 
		decrease_mList();

	// If the node has children we push the matrix
	}else{
		Mc result;
		result.count = count;	

		if(!mList.empty())
		{
			// sum the two latest matrices
			result.m = mList.front().m*m ;
		}else{
			// or if this is the first entry we add it as is
			result.m = m;
		}
		mList.push_front(result);
	}
}

/*
 * Name:	decrease_mList	
 * Purpose:	Pops entries that corresponds to already visited nodes.
 * 			Those are the entries that have had their 'count' reduced
 *	 		to 1. Also, reduce the next remaining entrys count 
 *			by 1 indicating that one subtree has been processed.
 * Input:	-
 * Output:	-
 * Misc:	-
 */
void RenderVisitor::decrease_mList()
{	
	std::list<Mc>::iterator it=mList.begin();
	// pop all entries with count reduced to 1.
	while( it->count <= 1 && it!= mList.end() )
	{
		it++;
		mList.pop_front();
	}
	// Reduce the count of the remaing top with one
	mList.front().count--;
}

/*
 * Name:	modify_sList
 * Purpose:	adds or removes entries in the sList 
 * Input:	-int count: the number of children in the node that called
 *			the method.
 *			State* s: The state of the node that called the method.
 * Output:	-
 * Misc:	Works almost exactly as modify_mList but instead of
 *			multiplyinh matrices it sums states
 */
void RenderVisitor::modify_sList(int count, State* s)
{
	if(count == 0)
	{
		decrease_sList();
	}else{
		Sc result;
		result.count = count;
		if(!sList.empty())
		{
			state_ptr oldState = sList.front().s;
			result.s = syncStates(oldState.get(), s);
		}else{
			result.s = state_ptr(new State());
			result.s->merge(s);
		}
		sList.push_front(result);
	}
}

/*
 * Name:	decrease_sList	
 * Purpose:	Decrease the sList after a leaf has been processed 
 * Input:	-	
 * Output:	-
 * Misc:	Works exactly as decrease_mList. Se that for a moder
 *			deetailed description.
 */
void RenderVisitor::decrease_sList()
{
	if(!sList.empty())
	{
		std::list<Sc>::iterator it=sList.begin();
		
		while( it->count <= 1 && it!= sList.end() )
		{
			it++;
			sList.pop_front();
		}
		sList.front().count--;
	}
}


/*
 * Name:	syncStates
 * Purpose: merges two states into a new state without affecting the
 *	 		input states.
 * Input:	State* lastState: The state that gets its attributes
 *			overridden.
 *			State* newState: The state that gets to override lastState
 * Output:	std::shared_ptr<State>: The sum of the previous states.
 * Misc:	-	
 */
state_ptr RenderVisitor::syncStates(State* lastState ,State* newState)
{
	state_ptr result = state_ptr(new State());

	result->merge(lastState);
	result->merge(newState);
	
	return result;
	
}
