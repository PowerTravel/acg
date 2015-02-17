#include "Scene.hpp"
#include "Geometry.hpp"
#include "Camera.hpp"
#include "Transform.hpp"
#include "Vec3.hpp"

#include "TransformSpinCallback.hpp"
#include "CameraMovementCallback.hpp"

Scene::Scene()
{
	root = std::shared_ptr<Group> (new Group);
}
Scene::~Scene()
{
	root = NULL;
}
Scene& Scene::getInstance()
{
	static Scene instance;
	return instance;
}

Group* Scene::getRoot()
{
	static Group* ptr = root.get();
	return ptr;
}

void Scene::buildScene()
{
	char V_SHADER[] = "shaders/vshader.glsl";
	char F_SHADER[] = "shaders/fshader.glsl";

	light_ptr  l1= light_ptr(new Light(Vec3(3,3,3), Vec4(0.2,0.2,0.2), Vec4(0.4,0.2,0.6), Vec4(0.1,0.5,0,1) ) );

	// Load Shader
	state_ptr statePtr = state_ptr(new State);
	statePtr->setShader( Shader(V_SHADER, F_SHADER));
	statePtr->getShader().use();
	statePtr->getShader().createUniform("MV");
	root->setState(statePtr);


	// construct Nodes` 
	camera_ptr cam = constructCamera(	statePtr, root, 
										Vec3(0.f, 0.f,-4.f),
										Vec3(0.f, 0.f,0.f),
										Vec3(0.f, 1.f, 0.f));
	cam->connectCallback(std::shared_ptr<CameraMovementCallback>(new CameraMovementCallback(cam)));

	transform_ptr p1 = constructTransform(	statePtr, cam,
											0.0, Vec3(0.f,0.f,-1.f),
											Vec3(-1.f,0.f,0.f),
											Vec3(1.f,1.f,1.f));

	p1->connectCallback(std::shared_ptr<TransformSpinCallback>( new TransformSpinCallback(p1)));

	transform_ptr p2 = constructTransform(	statePtr, cam,
											0.0, Vec3(0.f,0.f,-1.f),
											Vec3(1.f,0.f,0.f),
											Vec3(1.f,1.f,1.f));

	geometry_ptr g1 = constructGeometry(statePtr, p1, "models/box.obj");
	geometry_ptr g2 = constructGeometry(statePtr, p2, "models/sphere.obj");
	//geometry_ptr g3 = constructGeometry(statePtr, p1, "models/dragon2.off");
//	geometry_ptr g = constructGeometry(statePtr, p1, "models/5426_C3PO_Robot_Star_Wars.obj");
}

geometry_ptr Scene::constructGeometry(state_ptr s, group_ptr parent, const  char* fileName)
{
	geometry_ptr g = geometry_ptr(new Geometry(fileName));
	g->setState(s);
	parent->addChild(g);
	return g;
}

camera_ptr Scene::constructCamera(state_ptr s, group_ptr parent, Vec3 eye, Vec3 lookAt, Vec3 up)
{
	camera_ptr c= camera_ptr(new Camera());
	c->setState(s);
	parent->addChild(c);
	
	c->lookAt(eye, lookAt, up);
	c->setPerspectiveProjection();
	
	return c;
}

transform_ptr Scene::constructTransform(state_ptr s, group_ptr parent, float angle, Vec3 axis, Vec3 trans, Vec3 scale )
{
	transform_ptr t= transform_ptr(new Transform());
	t->setState(s);
	t->rotate(angle,axis);
	t->translate(trans);
	t->scale(scale);

	parent->addChild(t);
	return t;
}
