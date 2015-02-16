#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
//#include <GL/glut.h>
#include <GL/freeglut.h>
//#include <GL/freeglut_ext.h>
//#include "Shader.hpp"
//#include "Geometry.hpp"
//#include "Transform.hpp"
#include "Scene.hpp"
//#include "Camera.hpp"
#include "RenderVisitor.hpp"
#include "UpdateVisitor.hpp"
#include "KeyState.hpp"

#include <iostream>
#include <cstdio>

int SCREEN_WIDTH = 620;
int SCREEN_HEIGHT = 480;
int FPS = 60;

void setUpGlut(int argc, char* argv[]);
void GLEWprintSystemSpecs();
void setUpGlew();


void updateAndDisplay(int i);
void display();
void resize(int width, int height);
void idleFunk();
void glutKeyDownCallback(unsigned char key, int x, int y);
void glutKeyUpCallback(unsigned char key, int x, int y);
void glutSpecialKeyUpCallback(int key, int x, int y);
void glutSpecialKeyUpCallback(int key, int x, int y);

void glutMainProgram();

void reshape(int w, int h);

void testTriangle();
void testRectangle();
void testBox();
void testCube();

GLuint VAO;
GLuint VBO;
GLuint EBO;
GLuint program;

UpdateVisitor u;
RenderVisitor r;	 
int main(int argc, char* argv[])
{
	// Set up glut and glew
	setUpGlut(argc, argv);
	setUpGlew();

	Scene::getInstance().buildScene();
	KeyState::getInstance().setGlutCallback();

	glutMainProgram();	

	return 0;
}

void updateAndDisplay(int i)
{	
	u.traverse(Scene::getInstance().getRoot());
	display();

	glutTimerFunc(1000/FPS, updateAndDisplay,0);
}

void display()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//std::cout<<	"-=NEW DRAW=-  " <<Scene::getInstance().getRoot()->getNrChildren() << std::endl;
	
	r.traverse(Scene::getInstance().getRoot());
	
	glutSwapBuffers();
//	glutPostRedisplay();
//	glutTimerFunc(1000/60, display,0);
}

void setUpGlut(int argc, char* argv[])
{
	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);

	glutInitContextVersion(3,3);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutInitWindowPosition(50,50);
	glutCreateWindow("Assignment 1");
}

void resize(int width, int height)
{
	glViewport(0,0,width,height);
	display();
}

void idleFunk()
{
	
}

void glutKeyDownCallback(unsigned char key, int x, int y)
{
	if(key == 'q')
	{
		glutLeaveMainLoop();
	}
}
void glutKeyUpCallback(unsigned char key, int x, int y)
{

}
void glutSpecialKeyUpCallback(int key, int x, int y)
{

}
void glutSpecialKeyDownCallback(int key, int x, int y)
{

}
void glutMainProgram()
{
	//glutSetCursor(GLUT_CURSOR_NONE);
	glutDisplayFunc(display);
	glutReshapeFunc(resize);

	glutIgnoreKeyRepeat(1);
	//glutKeyboardFunc(glutKeyDownCallbackgt);
//	glutKeyboardUpFunc(glutKeyUpCallback);
//	glutSpecialFunc(glutSpecialKeyDownCallback);
//	glutSpecialUpFunc(glutSpecialKeyUpCallback);

	glutIdleFunc(idleFunk);

	updateAndDisplay(1);
	glutMainLoop();
}


//void resize(int width, int height)
//{
//    if(width<=height)
//    {
//        glViewport(0,(height-width)/2,width,width);
//    }else{
//       glViewport((width-height)/2,0,height,height);
//    }
//}


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
	if (glewInit() != GLEW_OK){
	  /* Problem: glewInit failed, something is seriously wrong. */
	    fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		exit(EXIT_FAILURE);
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

	glLineWidth(1.0);
	glPointSize(1.0);
	glClearColor(0.0,0.0,0.0,0.0);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
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
