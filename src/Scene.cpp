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

/*
 * Name:	BuildScene
 * Purpose:	Builds the scenegraph
 * Input:	Scene::BS bs: Enum specifying which scene to build
 * Output:	-
 * Misc:	-
 */

void Scene::buildScene(Scene::BS bs)
{
	if(bs == LAB1)
	{
		buildLab1();
	}else if(bs == LAB2){
		buildLab2();
	}else if(bs == LAB3){
		buildLab3();
	}
}

/*
 * Name:	linkGeometry
 * Purpose:	Looks up a geometry in a table and sets them as leafs 
 *			to a group.
 * Input:	-std::string name: The key for a Geometry in the table
 *			-std::shared_ptr<Group> grp: The parent to the geometries.
 * Output:	-
 * Misc:	-
 */
void Scene::linkGeometry(std::string name, group_ptr grp)
{
	geometry_vec g = gt[name.c_str()];
	for(int i = 0; i<g.size(); i++)
	{
		grp->addChild(g[i]);
	}
}

/*
 * Name:	loadGeometry
 * Purpose: Loads an .obj file and adds it to the local 
 *			geometry table.
 * Input:	-std::string name: The desired key for the Geometry 
 *			in the table.
 *			-std::string path: The path to the .obj file.
 * Output:	-
 * Misc:	-
 */
void Scene::loadGeometry(std::string name, std::string path)
{
	geometry_vec g1=  Geometry::loadFile(path.c_str());
	std::pair< std::string, geometry_vec > pair(name, g1);
	gt.insert(pair);
}

/*
 * Name:	constructCamera
 * Purpose: Builds a camera Node and attaches it to a parent
 * Input:	-State* s: The desired State of the node. Can be NULL.
 * 			-std::shared_ptr<Group> parent: The parent of the node
 *			-Vec3 eye: The position of the camera in world coordinates
 *			-Vec3 lookAT: The point the camera is looking at.
 *			-Vec3 up: The cameras up-direction
 * Output:	std::shared_ptr<Camera>: the newly constructed camera.
 * Misc:	-
 */
camera_ptr Scene::constructCamera(State* s, group_ptr parent, Vec3 eye, Vec3 lookAt, Vec3 up)
{
	// Create a new camera
	camera_ptr c= camera_ptr(new Camera());
	if(s!=NULL){
		// Give it a state
		c->setState(s);
	}
	// Set it as a child to the parent.
	parent->addChild(c);

	// Position the camera.
	c->lookAt(eye, lookAt, up);
	
	return c;
}

/*
 * Name:	constructTransform
 * Purpose: Builds a Transform Node and attaches it to a parent
 * Input:	-State* s: The desired State of the node. Can be NULL.
 * 			-std::shared_ptr<Group> parent: The parent of the node.
 *			-float angle: Angle of rotation
 *			-Vec3 axis: Axis of rotation
 *			-Vec3 trans: Translation vector
 *			-Vec3 scale: The scaling of the node
 * Output:	std::shared_ptr<Camera>: the newly constructed camera.
 * Misc:	-
 */
transform_ptr Scene::constructTransform(State* s, group_ptr parent, float angle, Vec3 axis, Vec3 trans, Vec3 scale )
{
	// Construct a new transform node
	transform_ptr t= transform_ptr(new Transform());
	if(s != NULL){
		// Add to it the desired state
		t->setState(s);
	}
	// Rotate, translate and scale it as necessary
	t->rotate(angle,axis);
	t->translate(trans);
	t->scale(scale);

	parent->addChild(t);
	return t;
}


/*
 * Name:	buldLab1
 * Purpose:	Constructrs the scene for lab 1
 * Input:	-
 * Output:	-
 * Misc:	-
 */
void Scene::buildLab1()
{
	// Load the relevant gemoetries from files
	gt = geometry_table();
	loadGeometry("cube", "models/box.obj");
	loadGeometry("sphere", "models/sphere.obj");
	loadGeometry("face", "models/Capsule/capsule.obj");


	// Load and initiate the shader and add it to the root node
	State s;
	setUpLab1ShaderState( &s );
	root->setState( &s );	
	
	
	// Create lights and add them to the root node
	State lightState = State();
	lightState.pushLight(Light(Vec3(0,0,0), Vec4(0.5,0.5,0.5), Vec4(0.5,0.5,0.5), Vec4(0.5,0.5,0.5), 0.002 ));
	lightState.pushLight(Light(Vec3(0,5,-10), Vec4(0.5,0.5,1.0), Vec4(0.5,0.5,1.0), Vec4(0.5,0.5,1.0), 0.002 ));
	lightState.pushLight(Light(Vec3(0,5,10), Vec4(1.5,0.5,0.5), Vec4(1.5,0.5,0.5), Vec4(1.0,0.5,0.5), 0.002 ));
	root->setState(&lightState);	


	// Construc the camera and attach it to root
	camera_ptr cam = constructCamera(	NULL , root, 
										Vec3(0.f, 0.f,4.f),
										Vec3(0.f, 0.f,0.f),
										Vec3(0.f, 1.f, 0.f));
	cam->connectCallback(std::shared_ptr<CameraMovementCallback>(new CameraMovementCallback(cam)));

	// Build the subtrees for the geometries
	constructSphere(cam);
	constructCubes(cam);
	constructFace(cam);
	// Create a geometry from hard code, not files.
	createFloor(cam);
}

// Below are helper-functions to buildLab1();
// The comments will be sparser.

// Declares the uniforms for the lab1 shader
void Scene::setUpLab1ShaderState(State* s)
{
	char V_SHADER[] = "shaders/lab1_vshader.glsl";
	char F_SHADER[] = "shaders/lab1_fshader.glsl";

	s->setShader( shader_ptr(new Shader(V_SHADER, F_SHADER)) );

	s->getShader()->use();
	//s->getShader()->createAttribute("vertex");
	//s->getShader()->createAttribute("normal");
	//s->getShader()->createAttribute("texCoord");
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
	s->getShader()->createUniform("nrLights");
}

// Constructs the spinning sphere for lab1 scene.
void Scene::constructSphere(group_ptr parent)
{
	// Create a state that renders lines.
	State lineState = State();
	lineState.setPolygonMode(State::LINE);
	lineState.setCullFace(false);

	// build the sphere
	transform_ptr sphere = constructTransform(	&lineState, parent,
											0.0, Vec3(0.f,0.f,-1.f),
											Vec3(0.f,0.f,0.f),
											Vec3(1.f,1.f,1.f));
	sphere->connectCallback(std::shared_ptr<TransformSpinCallback>( new TransformSpinCallback(sphere,0.005,Vec3(0,1,0))));

	linkGeometry("sphere", sphere);

}

// Builds the two spinning cubes for the lab1 scene.
void Scene::constructCubes(group_ptr parent)
{
	// Build the textured cube
	transform_ptr rot = constructTransform(	NULL, parent,
											0.0, Vec3(0.f,0.f,-1.f),
											Vec3(0.f,0.f,0.f),
											Vec3(1.f,1.f,1.f));
	rot->connectCallback(std::shared_ptr<TransformSpinCallback>( new TransformSpinCallback(rot, 0.01, Vec3(0,1,0) )));

	transform_ptr cube1 = constructTransform(	NULL, rot,
											3.1415/2, Vec3(0.f,0.f,1.f),
											Vec3(2.f,0.f,0.f),
											Vec3(1.f,1.f,1.f));
	cube1->connectCallback(std::shared_ptr<TransformSpinCallback>( new TransformSpinCallback(cube1, 0.05, Vec3(0,-1,0) )));
	linkGeometry("cube", cube1);	

	
	// Build the nontexture cube
	State noTex = State();
	noTex.setColorMaterial(true);
	noTex.setMaterial(Material::PLASTIC_GREEN);

	transform_ptr cube2 = constructTransform(	&noTex, rot,
											3.1415/2, Vec3(0.f,0.f,1.f),
											Vec3(-2.f,0.f,0.f),
											Vec3(1.f,1.f,1.f));
	cube2->connectCallback(std::shared_ptr<TransformSpinCallback>( new TransformSpinCallback(cube2, 0.05, Vec3(0,-1,0) )));
	linkGeometry("cube", cube2);	
}

// Construct the circling face for the lab1 scene
void Scene::constructFace(group_ptr parent)
{

	transform_ptr rotation = constructTransform(NULL, parent,0, Vec3(0.f,1.f,0.f), Vec3(0.f,0.f,0.f),Vec3(1.f,1.f,1.f));

	rotation->connectCallback(std::shared_ptr<TransformSpinCallback>( new TransformSpinCallback(rotation, 0.01, Vec3(0,0,1) )));

	transform_ptr offset = constructTransform(	NULL, rotation,3.1415/2, Vec3(0.f,1.f,0.f),Vec3(0.f,2.f,0.f),Vec3(1.f,1.f,1.f));

	offset->rotate(3.1415/2, Vec3(0.f,0.f,1.f));
	linkGeometry("face", offset);
}

// Creates the floor piece to show that we can load an
// object without a file for the lab1 scene.
void Scene::createFloor(group_ptr parent)
{

	int nrVert = 6*4;
	float vert[] = { 10,  0.05,  10.5,
					 10, -0.05,  10.5,
					 10, -0.05, -10.5,
					 10,  0.05, -10.5,
					-10,  0.05, -10.5,
					-10, -0.05, -10.5,
					-10, -0.05,  10.5,
					-10,  0.05,  10.5,
					 10,  0.05, -10.5,
					 10, -0.05, -10.5,
					-10, -0.05, -10.5,
					-10,  0.05, -10.5,
					-10,  0.05,  10.5,
					-10, -0.05,  10.5,
					 10, -0.05,  10.5,
					 10,  0.05,  10.5,
					-10,  0.05, -10.5,
					-10,  0.05,  10.5,
					 10,  0.05,  10.5,
					 10,  0.05, -10.5,
					-10, -0.05, -10.5,
					 10, -0.05, -10.5,
					 10, -0.05,  10.5,
					-10, -0.05,  10.5};
	
	float norm[] = {1, 0,  0, 
					1, 0,  0,
					1, 0,  0,
					1, 0,  0,
					-1, 0, 0,
					-1, 0, 0,
					-1, 0, 0,
					-1, 0, 0,
					0, 0, -1,
					0, 0, -1,
					0, 0, -1,
					0, 0, -1,
					0, 0,  1,
					0, 0,  1,
					0, 0,  1,
					0, 0,  1,
					0, 1,  0,
					0, 1,  0,
					0, 1,  0,
					0, 1,  0,
					0, -1, 0,
					0, -1, 0,
					0, -1, 0,
					0, -1, 0};
	int nrFaces = 12; 
 	int faces[] = {	 3,  0,  1, 
					 1,  2,  3,
					 7,  4,  5,
					 5,  6,  7,
					11,  8,  9,
					 9, 10, 11,
					15, 12, 13,
					13, 14, 15,
					19, 16, 17,
					17, 18, 19,
					23, 20, 21,
					21, 22, 23};

	// Build the geometry
	geometry_vec g = geometry_vec( );
	g.push_back(std::shared_ptr<Geometry>(new Geometry()) );
	g[0]->createGeom(nrVert, nrFaces, vert,  norm,  faces, NULL);
	
	State mat = State();
	mat.setMaterial(Material(Material::OBSIDIAN));
	mat.setColorMaterial(true);

	transform_ptr lower = constructTransform(&mat, parent, 0, Vec3(), Vec3(0,-4,0), Vec3(1,1,1) );

	std::pair< std::string, geometry_vec > pair("floor", g);
	gt.insert(pair);
	linkGeometry("floor", lower);
}

void Scene::buildLab2(){}
void Scene::buildLab3(){}
