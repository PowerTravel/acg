#include <GL/glew.h>
#include "RenderVisitor.hpp"
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
}

RenderVisitor::~RenderVisitor()
{

}

void RenderVisitor::apply(Geometry* g)
{
	push_sList(0, g->getState());
	
	mList.front().m.get(_M);
	state_ptr state = sList.front().s;
	if( state->isShaderSet() )
	{
		state->apply();
		shader_ptr shader = state->getShader();
		
		shader->setUniformMatrix(std::string("M"), _M);
		if(_isModelviewSet)
		{
			shader->setUniformMatrix(std::string("V"), _V);
			shader->setUniformMatrix(std::string("P"), _P);
		}else{
			std::cerr<<"No CameraMatrix active. Probably not rendering properly."<<std::endl;
		}
		g->draw();
	}else{
		std::cerr<<"No shader present. Not rendering geometry."<<std::endl;
	}
	
	decrease_sList();
	decrease_mList();
}

void RenderVisitor::printMatStruct()
{
	for(constListIt it = mList.begin(); it != mList.end(); it++)
	{
		std::cout<< it->count<< " ";
		//std::cout<< it->m << std::endl << std::endl;
	}
	std::cout << std::endl;
}

void RenderVisitor::apply(Group* grp)
{
	modify_mList(grp->childList.size(), Hmat());
	push_sList(grp->childList.size(), grp->getState());
}

void RenderVisitor::apply(Camera* cam)
{
	cam->getViewMat().get(_V);
	cam->getProjectionMat().get(_P);
	_isModelviewSet = true;
	//std::cout << "CAM" << std::endl;	
	//std::cout << _P << std::endl<<std::endl;
//	Hmat PV = _P*_V;

//	modify_mList(cam->childList.size(), PV);
	modify_mList(cam->childList.size(), Hmat());
	push_sList(cam->childList.size(), cam->getState());
}

void RenderVisitor::apply(Transform* t)
{	
	modify_mList(t->childList.size(), t->getM());
	push_sList(t->childList.size(), t->getState());
}

// Use for group nodes
void RenderVisitor::modify_mList(int count, Hmat m)
{
	// If the node is a leaf
	if(count == 0)
	{
		decrease_mList();
	// Else we push
	}else{
		Mc result;
		result.count = count;	
	
		if(!mList.empty())
		{
			result.m = mList.front().m*m ;
		}else{
			result.m = m;
		}
		mList.push_front(result);
	}
}

// Use for regular nodes
void RenderVisitor::decrease_mList()
{	
	std::list<Mc>::iterator it=mList.begin();
//	std::cout<< it->count << std::endl;	
	while( it->count <= 1 && it!= mList.end() )
	{
		it++;
		mList.pop_front();
	}
	mList.front().count--;
}

// use for leaf nodes
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

// Use for groups
void RenderVisitor::push_sList(int count, state_ptr s)
{
	// If the node is a leaf
	Sc result;
	result.count = count;
	if(!sList.empty())
	{
		state_ptr oldState = sList.front().s;
		if(s != NULL && oldState != NULL)
		{
			// Make sure to make a NEW copy when syncing
			// we dont want to modify existing states.
			result.s = syncStates(oldState, s);
		}else if(s == NULL && oldState != NULL ){
			result.s = oldState;
		}
		else if(s != NULL && oldState != NULL ){
			result.s = s;
		}else{
			result.s = NULL;
		}
	}else{
		result.s = s;
	}
	sList.push_front(result);
}

state_ptr RenderVisitor::syncStates(state_ptr lastState ,state_ptr newState)
{
	state_ptr result = state_ptr(new State());

	if(newState->isPolygonModeSet())
	{
		result->setPolygonMode( newState->getPolygonMode() );
	}else if(lastState->isPolygonModeSet()){
		result->setPolygonMode( lastState->getPolygonMode() );
	}

	if( newState->isShadeTypeSet() )
	{
		result->setShadeType( newState->getShadeType() );
	}else if( lastState->isShadeTypeSet() )
	{
		result->setShadeType( lastState->getShadeType() );
	}

	if( newState->isCullFaceSet() )
	{
		result->setCullFace( newState->getCullFace() );
	}else if( lastState->isCullFaceSet() )
	{
		result->setCullFace( lastState->getCullFace() );
	}

	if( newState->isColorMaterialSet() )
	{
		result->setColorMaterial(newState->getColorMaterial());
	}else if( lastState->isColorMaterialSet() )
	{
		result->setColorMaterial(lastState->getColorMaterial());
	}

	if( newState->isMaterialSet() )
	{
		result->setMaterial( newState->getMaterial() );
	}else if( lastState->isMaterialSet() )
	{
		result->setMaterial( lastState->getMaterial() );
	}

	if(newState->isShaderSet())
	{
		result->setShader(newState->getShader());
	}else if(lastState->isShaderSet())
	{
		result->setShader(lastState->getShader());
	}


	int n = lastState->getNrLights();
	int i = 0;
	while(i<n)
	{
		result->pushLight(lastState->getLight(i), lastState->isLightEnabled(i) );
		i++;
	}

	n = newState->getNrLights();
	i = 0;
	while(i<n)
	{
		result->pushLight(newState->getLight(i), newState->isLightEnabled(i) );
		i++;
	}

	n = lastState->getNrTextures();
	i = 0;
	while(i<n)
	{
		result->pushTexture(lastState->getTexture(i));
		i++;
	}

	n = newState->getNrTextures();
	i = 0;
	while(i<n)
	{
		result->pushTexture(newState->getTexture(i));
		i++;
	}

	return result;
	
}
