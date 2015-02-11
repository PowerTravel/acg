#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
//#include <GL/glut.h>
#include <GL/freeglut.h>
//#include <GL/freeglut_ext.h>
#include "Shader.hpp"
#include "Geometry.hpp"
#include "Transform.hpp"
#include "Scene.hpp"
//#include "NodeVisitor.hpp"
#include "RenderVisitor.hpp"
#include "UpdateVisitor.hpp"

#include <iostream>
#include <cstdio>

char V_SHADER[] = "shaders/vshader.glsl";
char F_SHADER[] = "shaders/fshader.glsl";

void setUpGlut(int argc, char* argv[]);
void GLEWprintSystemSpecs();
void display();
void setUpGlew();
void setUpCallbacks();

void reshape(int w, int h);

void testTriangle();
void testRectangle();
void testBox();
void testCube();

GLuint VAO;
GLuint VBO;
GLuint EBO;
GLuint program;

RenderVisitor renderVis;	

int main(int argc, char* argv[])
{
	// Set up glut and glew
	setUpGlut(argc, argv);
	setUpGlew();
	// Load Shaders, Add so that you get back a struct with the program id and the shader ids
	std::shared_ptr<State> statePtr = std::shared_ptr<State>(new State);
	statePtr->mShader = Shader(V_SHADER, F_SHADER);	
	statePtr->mShader.use();
	statePtr->mShader.createUniform("T"); //  Sets the Transfomation Uniform
	
	
	

	float angle = 0.0;
	Vec3 axis = Vec3(1,1,0);
	Vec3 trans = Vec3(0.0f,0.0f,0.0f);
	Vec3 scale = Vec3(1,1,1);
	
	std::shared_ptr<Transform> transPtr = std::shared_ptr<Transform>(new Transform(angle, axis, trans, scale));
	std::shared_ptr<Geometry> geomPtr = std::shared_ptr<Geometry>(new Geometry("models/box.obj") );
	transPtr->addChild(geomPtr);

	geomPtr->setState(statePtr);
	transPtr->setState(statePtr);
	Scene::getInstance().root->setState(statePtr);

	Scene::getInstance().root->addChild(transPtr);


	RenderVisitor r = RenderVisitor();	
	r.traverse(Scene::getInstance().root.get());

	
	setUpCallbacks();
	glutMainLoop();

	return 0;
}
 
void display()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		
	Scene::getInstance().root->update();
	renderVis.traverse(Scene::getInstance().root.get());


	glutSwapBuffers();
	glutPostRedisplay();
}

void setUpGlut(int argc, char* argv[])
{
	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

	glutInitContextVersion(3,3);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutInitWindowSize(1280, 720);
	glutInitWindowPosition(10,10);
	glutCreateWindow("GLUT Viewer");
}

void GLEWprintSystemSpecs()
{
	const GLubyte* vendor = glGetString(GL_VENDOR);
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	const GLubyte* shading = glGetString(GL_SHADING_LANGUAGE_VERSION);
	
	GLint numExt;
	glGetIntegerv(GL_NUM_EXTENSIONS, &numExt);

	GLint numLang; 
	glGetIntegerv(GL_NUM_SHADING_LANGUAGE_VERSIONS, &numLang);
	const GLubyte* extension = glGetStringi(GL_EXTENSIONS, numExt-1 );
	const GLubyte* shadeVers = glGetStringi(GL_SHADING_LANGUAGE_VERSION, numLang-1 );

	fprintf(stderr, "\n -=System Specs=- \n");
	fprintf(stderr, "vendor = %s \n", vendor);
	fprintf(stderr, "renderer = %s \n", renderer);
	fprintf(stderr, "GL Version = %s \n", version);
	fprintf(stderr, "Shading language version = %s \n", shading);
	fprintf(stderr, "shading extenstion = %s \n\n", extension);

}

void setUpGlew()
{
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err){
	  /* Problem: glewInit failed, something is seriously wrong. */
	    fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
/*
	if(	glewGetExtension("GL_ARB_fragment_shader") != GL_TRUE ||
		glewGetExtension("GL_ARB_vertex_shader") != GL_TRUE ||
		glewGetExtension("GL_ARB_shader_objects") != GL_TRUE ||
		glewGetExtension("GL_ARB_shading_language_100") != GL_TRUE  )
	{
		std::cerr << "Driver does not support OpenGL shading language" << std::endl;
		exit(1);
	}
*/
	GLEWprintSystemSpecs();	
}

void resize(int width, int height)
{
    if(width<=height)
    {
        glViewport(0,(height-width)/2,width,width);
    }else{
        glViewport((width-height)/2,0,height,height);
    }
}

void setUpCallbacks()
{
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
}






















void testBox()
{
	float vertices[] {	
						0.5f, 0.5f, 0.5f,	
						0.5f, -0.5f, 0.5f,	
						0.5f, -0.5f, -0.5f,	
						0.5f, 0.5f, -0.5f,

						-0.5f, 0.5f, -0.5f,	
						-0.5f, -0.5f, -0.5f,	
						-0.5f, -0.5f, 0.5f,	
						-0.5f, 0.5f, 0.5f,
						
						0.5f, 0.5f, -0.5f,	
						0.5f, -0.5f, -0.5f,	
						-0.5f, -0.5f, -0.5f,	
						-0.5f, 0.5f, -0.5f,
						
						-0.5f, 0.5f, 0.5f,	
						-0.5f, -0.5f, 0.5f,	
						0.5f, -0.5f, 0.5f,	
						0.5f, 0.5f, 0.5f,

						-0.5f, 0.5f, -0.5f,	
						-0.5f, 0.5f, 0.5f,	
						0.5f, 0.5f, 0.5f,	
						0.5f, 0.5f, -0.5f,	
						
						-0.5f, -0.5f, -0.5f,	
						0.5f, -0.5f, -0.5f,	
						0.5f, -0.5f, 0.5f,	
						-0.5f, -0.5f, 0.5f};
	int faces[] = {	3,0,1,
					1,2,3,
					7,4,5,
					5,6,7,
					11,8,9,
					9,10,11,
					15,12,13,
					13,14,15,
					19,16,17,
					17,18,19,
					23,20,21,
					21,22,23};
	
	glGenVertexArrays(1,&VAO);
	glGenBuffers(1,&VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(faces), faces, GL_STATIC_DRAW);

	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void testTriangle()
{
	float vertices[] = {-0.5f, -0.5f,
					0.5f, -0.5f,
					0.0f, 0.5f};

	glGenVertexArrays(1,&VAO);
	glGenBuffers(1,&VBO);
	glBindVertexArray(VAO);
	

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

}
void testRectangle()
{
	GLfloat vertices[] = {0.5f, 0.5f,
						0.5f, -0.5f,
						-0.5f, -0.5f,
						-0.5f, 0.5f};
	GLuint indices[] = {0,1,3,
						1,2,3};

	
	glGenVertexArrays(1,&VAO);
	glGenBuffers(1,&VBO);
	glGenBuffers(1, &EBO);
	
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void testCube()
{
	GLfloat vertices[] { -0.5f, -0.5f, -0.5f,
						 0.5f, -0.5f, -0.5f,
						 0.5f, -0.5f, 0.5f,
						-0.5f, -0.5f, 0.5f,
						 -0.5f, 0.5f, 0.5f,
						 0.5f, 0.5f, 0.5f,
						 0.5f, 0.5f, -0.5f,
	 					-0.5f, 0.5f, -0.5f};

	GLuint indices[] = {6,3,2,7,
						8,1,4,5,
						7,2,1,8,
						5,4,3,6,
						8,5,6,7,
						1,2,3,4};

	glGenVertexArrays(1,&VAO);
	glGenBuffers(1,&VBO);
	glGenBuffers(1, &EBO);
	
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

}
