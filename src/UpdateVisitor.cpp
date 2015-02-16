#include "UpdateVisitor.hpp"
#include "Transform.hpp"
UpdateVisitor::UpdateVisitor(){}

UpdateVisitor::~UpdateVisitor(){}

void UpdateVisitor::apply(Geometry* g)
{
//	printf("Visiting Geometry from UpdateVisitor\n");
}

void UpdateVisitor::apply(Group* grp)
{
//	printf("Visiting Group from UpdateVisitor\n");
}

void UpdateVisitor::apply(Transform* t)
{
	//printf("Visiting Transform from UpdateVisitor\n");
	t->update();
}

void UpdateVisitor::apply(Camera* cam)
{
	//printf("Visiting Camera from UpdateVisitor\n");
}
