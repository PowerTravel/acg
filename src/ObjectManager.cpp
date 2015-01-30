#include "ObjectManager.hpp"

ObjectManager::ObjectManager()
{

}

ObjectManager::~ObjectManager()
{
	while(!objects.isEmpty())
	{
		objects.pop_back();
	}
}

ObjectManager::loadFile(static char[] filename)
{

}
