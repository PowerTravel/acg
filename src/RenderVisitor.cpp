#include <GL/glew.h>
#include "RenderVisitor.hpp"
#include "Transform.hpp"
#include "Geometry.hpp"
#include "Camera.hpp"
#include <iostream>

RenderVisitor::RenderVisitor()
{
	mList =std::list<Mc>();
}

RenderVisitor::~RenderVisitor()
{

}

void RenderVisitor::apply(Geometry* g)
{
	State* state = g->getState().get();
	Shader s = state->getShader();

	float m[16];
	mList.front().m.get(m);
	s.setUniformMatrix(std::string("MV"), m);
	g->draw();

	decrease_mList();
}

void RenderVisitor::printMatStruct()
{
	for(constListIt it = mList.begin(); it != mList.end(); it++)
	{
		//std::cout<< it->count<< " ";
		std::cout<< it->m << std::endl << std::endl;
	}
	std::cout << std::endl;
}

void RenderVisitor::apply(Group* grp)
{
//	printf("Group\n");
}

void RenderVisitor::apply(Camera* cam)
{
	Hmat V = cam->getViewMat();
	Hmat P = cam->getProjectionMat();
	Hmat PV = P*V;
	modify_mList(cam->childList.size(), PV);
}

void RenderVisitor::apply(Transform* t)
{	
	modify_mList(t->childList.size(), t->getM());
}

void RenderVisitor::modify_mList(int count, Hmat m)
{
	if(count == 0)
	{
		decrease_mList();
	}else{
		Mc result;
		result.count = count;	
		result.m = m;
	
		if(!mList.empty())
		{
			result.m = mList.front().m*m ;
		}
		mList.push_front(result);
	}
}

void RenderVisitor::decrease_mList()
{	
	std::list<Mc>::iterator ci=mList.begin();
	
	bool stop = false;
	int i = 0;
	while( ci->count <= 1 && ci!= mList.end() )
	{
		i++;
		ci++;
		mList.pop_front();
	}
	mList.front().count --;
}


void RenderVisitor::updateState(State* st)
{
		
}
