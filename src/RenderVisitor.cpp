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
	mList.front().m.get(_M);
	
	state_ptr state = syncStates(sList.front().s.get(),g->getState() );

	if( state->isShaderSet() )
	{

		if(sList.front().s->isMaterialSet())
		{
			state->setMaterial(sList.front().s->getMaterial());
		}

		state->apply();
		shader_ptr shader = state->getShader();
		
		shader->setUniformMatrix("M",1, _M);
		if(_isModelviewSet)
		{
			shader->setUniformMatrix("V", 1, _V);
			shader->setUniformMatrix("P", 1, _P);
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
//	printf("Visiting Group from Render\n");
	modify_mList(grp->childList.size(), Hmat());
	modify_sList(grp->childList.size(), grp->getState());
}

void RenderVisitor::apply(Camera* cam)
{
//	printf("Visiting Camera from Render\n");
	cam->getViewMat().get(_V);
	cam->getProjectionMat().get(_P);
	_isModelviewSet = true;
	
	modify_mList(cam->childList.size(), Hmat());
	modify_sList(cam->childList.size(), cam->getState());
}

void RenderVisitor::apply(Transform* t)
{	
//	printf("Visiting Transform from Render\n");
	modify_mList(t->childList.size(), t->getM());
	modify_sList(t->childList.size(), t->getState());
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

state_ptr RenderVisitor::syncStates(State* lastState ,State* newState)
{
	state_ptr result = state_ptr(new State());

	result->merge(lastState);
	result->merge(newState);
	
	return result;
	
}
