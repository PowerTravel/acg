#ifndef SCENE_HPP
#define SCENE_HPP

#include "Group.hpp"
#include <vector>
#include <unordered_map>

#ifndef STATE_PTR
#define STATE_PTR
class State;
typedef std::shared_ptr<State> state_ptr;
#endif // STATE_PTR

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

#ifndef GEOM_TABLE
#define GEOM_TABLE
class Geometry;
typedef std::unordered_map< std::string,  geometry_vec  >  geometry_table;
#endif //GEOM_TABLE

class Vec3;

/*	Class: 		Scene
 *	Purpose: 	Constructs the scenegraph with all models states 
 *				and animations.
 *	Misc:		It is a singleton.
 */
class Scene{

	public:
		
		enum BS{
			LAB1,
			LAB2,
			LAB3
		};

		static Scene& getInstance();
		Group* getRoot();

		void buildScene(Scene::BS);
	private:
		// The root node of the scenegraph
		std::shared_ptr<Group> root;
		// A table of all loaded geometries. 
		// Each entry is a vector carrying many geometries
		// Each vector corresponds to an .obj file
		geometry_table gt;	


		Scene();
		virtual ~Scene();

		Scene(Scene const&) = delete;
		void operator=(Scene const&) = delete;


		// Makes it easy to load a geometry
		void loadGeometry(std::string name, std::string path);
		// Links a geometry to a group node
		void linkGeometry(std::string name, group_ptr grp);

		// Makes it easy to set up a camera.
		camera_ptr constructCamera(State* s, group_ptr parent, Vec3 eye, Vec3 lookAt, Vec3 up);
		// Makes it easy to set up a transformation Group
		transform_ptr constructTransform(State* s, group_ptr parenti, float angle, Vec3 axis, Vec3 trans, Vec3 scale );


		// Functions related to constructing the scene in lab1
		void buildLab1();
			void createFloor(group_ptr parent);
			void setUpLab1ShaderState(State* s);
			void constructFace(group_ptr parent);
			void constructCubes(group_ptr parent);
			void constructSphere(group_ptr parent);
		void buildLab2();
		void buildLab3();
};

#endif // SCENE_HPP
