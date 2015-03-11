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
	std::list<aggregate_data> aList;
	_isModelviewSet = false;
}

RenderVisitor::~RenderVisitor()
{

}

void RenderVisitor::apply(RenderToTexture* tex)
{
	modify_aList(tex->childList.size(), Hmat(), tex->getState(), tex);
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
	aList.front().m.get(_M);
	
	// We sync the geometries state with the lates entry in the aList.
	state_ptr state = syncStates(aList.front().s.get(),g->getState() );
	float shadowBiasPVM[16];
	Hmat I = Hmat();
	I.get(shadowBiasPVM);
	if( state->isShaderSet() )
	{
		// First we render the depthMap since it will be the same
		// each time and don't depend on the State
		RenderToTexture* rtt = aList.front().rtt;
		if(rtt != NULL && state->getNrLights() != 0)
		{
		
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);

			Shader* ss = rtt->getShader();
			ss->use();

			// Object position, Light poistion
			Vec3 op, lp;
			// Get the position of the object being illuminated
			int dim = 4;
			for(int i=0; i<dim-1; i++)
			{
				op[i] = _M[dim*i+3];
			}	
			// Get the position of the first light
			lp = state->getLight(0).getPosition();
			Camera lc = Camera(lp, op, Vec3(0,1,0));
			
			float lView[16], lProj[16];
			lc.getViewMat().get(lView);
			lc.getProjectionMat().get(lProj);

			ss->setUniformMatrix("M", 1, _M);
			ss->setUniformMatrix("V", 1, lView);
			ss->setUniformMatrix("P", 1, lProj);	
	
			rtt->bindBuffer();

			g->draw();

			rtt->clearBuffer();

			Hmat mtmp = Hmat(_M);
			Hmat vtmp = Hmat(lView);
			Hmat ptmp = Hmat(lProj);

			float biasf[] = { 0.5,0,0,0.5,
							 0,0.5,0,0.5,
							 0,0,0.5,0.5,
							 0,0,0, 1};
			Hmat bias = Hmat(biasf);


			Hmat pvmTmp;
			pvmTmp = vtmp*mtmp;
			pvmTmp = ptmp*pvmTmp;
			pvmTmp = bias*pvmTmp;
			pvmTmp.get(shadowBiasPVM);	
		}

		// If a material is set previously it overrides
		// any material that may have been loaded to the 
		// geometry from a file.
		if(aList.front().s->isMaterialSet())
		{
			state->setMaterial(aList.front().s->getMaterial());
		}

		// Apply the state to openGL
		state->apply();
		
		initTextures(state.get());

		// Send the Model View and projection matrices to the shader
		sendPVMtoGPU(state->getShader());

		if(rtt != NULL && state->getNrLights()!=0){
			state->getShader()->setUniformMatrix("BiasLightPVM", 1, shadowBiasPVM);
		}

		// draw the geometry
		g->draw();
	}else{
		std::cerr<<"No shader present. Not rendering geometry."<<std::endl;
	}

	// Since we are in a leaf we now want to erase all entries
	// in these lists up to the entry that has unvisited children.
	decrease_aList();
}

void RenderVisitor::initTextures(State* s)
{
	Shader* shade = s->getShader().get();
	if(s->hasTexture(State::DIFFUSE) && !s->getColorMaterial()){
		// Tell shader we are using a diffuseTexture
		int useDiffuse = 1;
		shade->setUniform1i("usingDiffTexture",1, &useDiffuse);
	
		s->getTexture(State::DIFFUSE).bind(GL_TEXTURE0);
		int tex = 0;
		shade->setUniform1i("diffuseTextureID",1, &tex);
	}else{
		// unbind any loaded textures
		glBindTexture(GL_TEXTURE_2D,0);
		int useDiffuse = 0;
		shade->setUniform1i("usingDiffTexture",1, &useDiffuse);
	}

	RenderToTexture* rtt = aList.front().rtt;
	if(aList.front().rtt != NULL)
	{
		int useShadow= 1;
		shade->setUniform1i("usingShadowMap",1, &useShadow);

		rtt->bindTexture(GL_TEXTURE1);
		int shd = 1;
		shade->setUniform1i("shadowMapID",1, &shd);
	}else{
		glBindTexture(GL_TEXTURE_2D,0);
		int useShadow = 0;
		shade->setUniform1i("usingShadowMap",1, &useShadow);
	}
}


void RenderVisitor::sendPVMtoGPU(shader_ptr s)
{
		s->setUniformMatrix("M",1, _M);
		if(_isModelviewSet)
		{
			s->setUniformMatrix("V", 1, _V);
			s->setUniformMatrix("P", 1, _P);
		}else{
			std::cerr<<"No CameraMatrix active. Probably not rendering properly."<<std::endl;
		}
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
	// But it may have children and a state, thus we add a unit matrix
	// together with the number of children it has.
	modify_aList(grp->childList.size(), Hmat(), grp->getState(), NULL);
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
	modify_aList(cam->childList.size(), Hmat(), cam->getState(), NULL);
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
	modify_aList(t->childList.size(), t->getM(), t->getState(), NULL);
}

/*
 * Name:	modify_aList	
 * Purpose: Adds or removes entries in the aList
 * Input:	-int count: The number of children the added Hmat
 *			will be relevant for.
 *			-Hmat m: The matrix to be summed up.
 *			-State* s: The state that should be accumulated
 *			-RenderToTexture* t: If we want to render to a texture
 *			instead of to the screen
 * Output:	-
 * Misc:	-
 */
void RenderVisitor::modify_aList(int count, Hmat m, State* s, RenderToTexture* t )
{
	// If the node is a leaf
	if(count == 0)
	{	
		// If we are in a leaf we have to popp all entries
		// that corresponds to already visited nodes with
		// no children. Those entries are the ones where 
		// 'count' has been reduced to 1; 
		decrease_aList();

	// If the node has children we push the matrix
	}else{
		aggregate_data result;
		result.count = count;	
		
		if(aList.empty()){
			// or if this is the first entry we add it as is
			result.m = m;
			
			result.s = state_ptr(new State());
			result.s->merge(s);

			result.rtt = t;
		}else{
			// sum the two latest matrices
			result.m = aList.front().m*m ;
			
			state_ptr oldState = aList.front().s;
			result.s = syncStates(oldState.get(), s);

			if(t != NULL){
				result.rtt = t;	
			}else{
				result.rtt = aList.front().rtt;
			}
		}	

		aList.push_front(result);
	}
}


/*
 * Name:	decrease_aList	
 * Purpose:	Pops entries that corresponds to already visited nodes.
 * 			Those are the entries that have had their 'count' reduced
 *	 		to 1. Also, reduce the next remaining entrys count 
 *			by 1 indicating that one of its childs subtree has been
 *			processed.
 * Input:	-
 * Output:	-
 * Misc:	-
 */
void RenderVisitor::decrease_aList()
{	
	std::list<aggregate_data>::iterator it=aList.begin();
	// pop all entries with count reduced to 1.
	while( it->count <= 1 && it!= aList.end() )
	{
		it++;
		aList.pop_front();
	}
	// Reduce the count of the remaing top with one
	aList.front().count--;
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
