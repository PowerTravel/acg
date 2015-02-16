#include "UpdateVisitor.hpp"
#include "Transform.hpp"
#include "Camera.hpp"
#include "Geometry.hpp"
UpdateVisitor::UpdateVisitor(){}

UpdateVisitor::~UpdateVisitor(){}

void UpdateVisitor::apply(Geometry* g)
{
//	printf("Visiting Geometry from UpdateVisitor\n");
	g->update();
}

void UpdateVisitor::apply(Group* grp)
{
//	printf("Visiting Group from UpdateVisitor\n");
	grp->update();
}

void UpdateVisitor::apply(Transform* t)
{
	//printf("Visiting Transform from UpdateVisitor\n");
	t->update();
}

void UpdateVisitor::apply(Camera* cam)
{
	cam->update();
	//printf("Visiting Camera from UpdateVisitor\n");
}
