#include <GL/glew.h>
#include "RenderVisitor.hpp"
#include "Transform.hpp"
#include "Geometry.hpp"
#include <iostream>

RenderVisitor::RenderVisitor()
{
	mList =std::list<Mc>();
	vList =std::list<Mc>();
}

RenderVisitor::~RenderVisitor()
{

}

void RenderVisitor::apply(Geometry* g)
{

	State* state = g->getState().get();
	Shader s = state->mShader;
	

	float m[16];
	mList.front().m.get(m);
	s.setUniformMatrix(std::string("T"), m);	

/*
	std::cout << "=============" <<std::endl;
	std::cout << mList.front().m<<std::endl;
	std::cout << "--------------" <<std::endl;
	Hmat hh = Hmat(m);
	std::cout << hh<<std::endl;
	std::cout << "--------------" <<std::endl;
	for(int i = 0; i<4; i++)
	{
		for(int j = 0; j<4; j++)
		{
			std::cout << m[4*i+j]<< " ";
		}
		std::cout << std::endl;
	}
	std::cout << "=============" <<std::endl;
*/

	g->draw();
	decrease_mList();
}

void RenderVisitor::decrease_mList()
{	
	//std::list::const_iterator ci;
	for(std::list<Mc>::const_iterator ci=mList.begin(); ci!= mList.end(); ci++)
	{
		Mc mc = *ci;
		mc.count--;
		if(mc.count <= 0)
		{
			mList.pop_front();
			ci=mList.begin();
		}
		//std::cerr<<mc.count<<std::endl;
	}

/*
	bool done = false;
	while( !mList.empty() && !done )
	{
		ci = mList.begin();
		if( ci->count == 0 )
		{
			mList.pop_front();
		}else{
			done = true;
		}
	}
*/
}

void RenderVisitor::apply(Group* grp)
{
	//printf("Visiting Group from RenderVisitor\n");
}

void RenderVisitor::apply(Transform* t)
{	
	Mc result;

	result.count = t->childList.size();
	if(mList.empty())
	{
		result.m = t->getModelMatrix();
	}else{
		Hmat m1, m2;
		m1 = t->getModelMatrix();
		m2 = mList.front().m;
		result.m = m1*m2;
	}

	mList.push_front(result);

	//printf("Visiting Transform from RenderVisitor\n");
}
