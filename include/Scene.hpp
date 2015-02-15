#ifndef SCENE_HPP
#define SCENE_HPP

#include "Group.hpp"

class Scene{

	public:
		static Scene& getInstance()
		{
			static Scene instance;
			return instance;
		
		}
		Group* getRoot()
		{
			return root.get();
		}
	private:
		std::shared_ptr<Group> root;
		
		Scene(){
			root = std::shared_ptr<Group> (new Group);
		};
		virtual ~Scene()
		{
			root = NULL;
		}
		Scene(Scene const&) = delete;
		void operator=(Scene const&) = delete;

};

#endif // SCENE_HPP
