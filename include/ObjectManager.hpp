#ifndef OBJECT_MANAGER_HPP
#define OBJECT_MANAGER_HPP

#include "Vec3.h"

class ObjectManager{

	public:
		ObjectManager();
		virtual ~ObjectManager();

		bool loadFile(static char[] filename);

	private:
		struct object{
			int ID;
			char name[];
			std::shared_ptr()<Vec3> obj;
			std::shared_ptr()<Vec3> norm;
		};
		
		std::vector<object> objects;
};


#endif //OBJECT_MANAGER_HPP
