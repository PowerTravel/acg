#include <cstdio>
#include "ObjectManager.hpp"
int main()
{
	glewInit();
	ObjectManager objMan = ObjectManager();
	objMan.loadFile("../models/box.obj");
	return 0;
}
