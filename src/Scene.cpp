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

	// Load Shader
	State s;
	setUpShaderState( &s );
	root->setState( &s );	
	root->getState()->pushLight(Light(Vec3(4,4,4), Vec4(1,1,1), Vec4(1,1,1), Vec4(1,1,1), 0.2 ));

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
	g3[0]->getState()->setMaterial(Material(Material::RUBBER_RED));
	//geometry_vec g5 = constructGeometry(NULL, still, "../vrlib/models/Paris/paris.obj");
//	geometry_vec g4 = constructGeometry(NULL, still, "models/5426_C3PO_Robot_Star_Wars.obj");
}

void Scene::setUpShaderState(State* s)
{
	char V_SHADER[] = "shaders/vshader.glsl";
	char F_SHADER[] = "shaders/fshader.glsl";

	s->setShader( shader_ptr(new Shader(V_SHADER, F_SHADER)) );

	s->getShader()->use();
	s->getShader()->createUniform("vPos");
	s->getShader()->createUniform("M");
	s->getShader()->createUniform("V");
	s->getShader()->createUniform("P");
	s->getShader()->createUniform("ambientProduct");
	s->getShader()->createUniform("diffuseProduct");
	s->getShader()->createUniform("specularProduct");
	s->getShader()->createUniform("lightPosition");
	s->getShader()->createUniform("attenuation");
	s->getShader()->createUniform("shininess");
	s->getShader()->createUniform("gSampler");
	s->getShader()->createUniform("usingTexture");
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
