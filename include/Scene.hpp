#ifndef SCENE_HPP
#define SCENE_HPP

#include "Group.hpp"
#include <vector>
#ifndef GEOMETRY_VEC
#define GEOMETRY_VEC
class Geometry;
typedef std::vector< std::shared_ptr<Geometry> > geometry_vec;
#endif //GEOMETRY_VEC

#ifndef TRANSFORM_PTR
#define TRANSFORM_PTR
class Transform;
typedef std::shared_ptr<Transform> transform_ptr;
#endif // TRANSFORM_PTR

#ifndef CAMERA_PTR
#define CAMRA_PTR
class Camera;
typedef std::shared_ptr<Camera> camera_ptr;
#endif //CAMERA_PTR

class Vec3;

class Scene{

	public:
		static Scene& getInstance();
		Group* getRoot();

		void buildScene();
	private:
		std::shared_ptr<Group> root;
		
		Scene();
		virtual ~Scene();

		Scene(Scene const&) = delete;
		void operator=(Scene const&) = delete;

		geometry_vec constructGeometry(state_ptr s, group_ptr parent, const char* fileName);
		camera_ptr constructCamera(state_ptr s, group_ptr parent, Vec3 eye, Vec3 lookAt, Vec3 up);
		transform_ptr constructTransform(state_ptr s, group_ptr parenti, float angle, Vec3 axis, Vec3 trans, Vec3 scale );
};

#endif // SCENE_HPP
