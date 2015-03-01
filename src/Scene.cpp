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

	light_ptr  l1= light_ptr(new Light(Vec3(0,0,0), Vec4(0.2,0.2,0.2), Vec4(0.4,0.2,0.6), Vec4(0.1,0.5,0,1), 0.2 ) );

	// Load Shader

	state_ptr shaderStatePtr = setUpShaderState();
	root->setState( shaderStatePtr.get() );
	

	camera_ptr cam = constructCamera(	NULL , root, 
										Vec3(0.f, 0.f,4.f),
										Vec3(0.f, 0.f,0.f),
										Vec3(0.f, 1.f, 0.f));
	cam->connectCallback(std::shared_ptr<CameraMovementCallback>(new CameraMovementCallback(cam)));

	transform_ptr sphere = constructTransform(	NULL, cam,
											0.0, Vec3(0.f,0.f,-1.f),
											Vec3(0.f,0.f,0.f),
											Vec3(1.f,1.f,1.f));
	sphere->connectCallback(std::shared_ptr<TransformSpinCallback>( new TransformSpinCallback(sphere)));

	transform_ptr orbit = constructTransform(	NULL, sphere,
											0.0, Vec3(0.f,0.f,-1.f),
											Vec3(2.f,0.f,0.f),
											Vec3(1.f,1.f,1.f));
	orbit->connectCallback(std::shared_ptr<TransformSpinCallback>( new TransformSpinCallback(orbit, 0.05, Vec3(0,-1,0) )));

	transform_ptr still = constructTransform(	NULL, cam,
											3.1415/2, Vec3(1.f,0.f,0.f),
											Vec3(0.f,2.f,0.f),
											Vec3(1.f,1.f,1.f));

	State lineState = State();
	lineState.setPolygonMode(State::LINE);
	lineState.setCullFace(false);
	

	geometry_vec g1 = constructGeometry(NULL, orbit, "models/box.obj");
	geometry_vec g2 = constructGeometry(&lineState, sphere, "models/sphere.obj");
	geometry_vec g3 = constructGeometry(NULL, still, "models/Capsule/capsule.obj");
//	geometry_vec g3 = constructGeometry(NULL, still, "models/5426_C3PO_Robot_Star_Wars.obj");
}

state_ptr Scene::setUpShaderState()
{
	char V_SHADER[] = "shaders/vshader.glsl";
	char F_SHADER[] = "shaders/fshader.glsl";

	state_ptr statePtr = state_ptr(new State);
	
	statePtr->setShader( shader_ptr(new Shader(V_SHADER, F_SHADER)) );

	statePtr->getShader()->use();
	statePtr->getShader()->createUniform("M");
	statePtr->getShader()->createUniform("V");
	statePtr->getShader()->createUniform("P");
	statePtr->getShader()->createUniform("ambientProduct");
	statePtr->getShader()->createUniform("diffuseProduct");
	statePtr->getShader()->createUniform("specularProduct");
	statePtr->getShader()->createUniform("lightPosition");
	statePtr->getShader()->createUniform("attenuation");
	statePtr->getShader()->createUniform("shininess");

	return statePtr;
}

geometry_vec Scene::constructGeometry(State* s, group_ptr parent, const  char* fileName)
{
	geometry_vec g_vec=  Geometry::loadFile(fileName);
	for(int i = 0; i< g_vec.size(); i++)
	{
		parent->addChild(g_vec[i]);
		if(s!=NULL){
			g_vec[i]->setState(s);
		}
	}
	return g_vec;
}

camera_ptr Scene::constructCamera(State* s, group_ptr parent, Vec3 eye, Vec3 lookAt, Vec3 up)
{
	camera_ptr c= camera_ptr(new Camera());
	if(s!=NULL){
		c->setState(s);
	}
	parent->addChild(c);
	
	c->lookAt(eye, lookAt, up);
	c->setPerspectiveProjection();
	
	return c;
}

transform_ptr Scene::constructTransform(State* s, group_ptr parent, float angle, Vec3 axis, Vec3 trans, Vec3 scale )
{
	transform_ptr t= transform_ptr(new Transform());
	if(s != NULL){
		t->setState(s);
	}
	t->rotate(angle,axis);
	t->translate(trans);
	t->scale(scale);

	parent->addChild(t);
	return t;
}
