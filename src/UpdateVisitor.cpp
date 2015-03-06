#include "UpdateVisitor.hpp"
#include "Transform.hpp"
#include "Camera.hpp"
#include "Geometry.hpp"
UpdateVisitor::UpdateVisitor(){}

UpdateVisitor::~UpdateVisitor(){}

void UpdateVisitor::apply(Geometry* g)
{
	g->update();
}

void UpdateVisitor::apply(Group* grp)
{
	grp->update();
}

void UpdateVisitor::apply(Transform* t)
{
	t->update();
}

void UpdateVisitor::apply(Camera* cam)
{
	cam->update();
}
