#include "RenderVisitor.hpp"
#include "Geometry.hpp"

RenderVisitor::RenderVisitor()
{

}

RenderVisitor::~RenderVisitor()
{

}

void RenderVisitor::apply(Geometry* g)
{
	g->draw();
}

void RenderVisitor::apply(Group* grp)
{
	//printf("Visiting Group from RenderVisitor\n");
}

void RenderVisitor::apply(Transform* t)
{
	//printf("Visiting Transform from RenderVisitor\n");
}
