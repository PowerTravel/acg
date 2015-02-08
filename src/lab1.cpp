#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
//#include <GL/glut.h>
#include <GL/freeglut.h>
//#include <GL/freeglut_ext.h>
#include "Shader.hpp"
#include "Geometry.hpp"

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
Geometry g;

int main(int argc, char* argv[])
{
	// Set up glut and glew
	setUpGlut(argc, argv);
	setUpGlew();
	// Load Shaders, Add so that you get back a struct with the program id and the shader ids
//	program = initProgram("shaders/vshader.glsl", "shaders/fshader.glsl");
//	glUseProgram(program);

	std::shared_ptr<State>  statePtr = std::shared_ptr<State>(new State);
	statePtr->mShader = Shader("shaders/vshader.glsl", "shaders/fshader.glsl");
	
	g = Geometry("models/box.obj");	
	g.setState(statePtr);


	setUpCallbacks();
	


	glutMainLoop();

	return 0;
}
 
void testBox()
{
	float vertices[] {	0.5f, 0.5f, 0.5f,	
						0.5f, -0.5f, 0.5f,	
						0.5f, -0.5f, -0.5f,	
						0.5f, 0.5f, -0.5f,

						-0.5f, 0.5f, -0.5f,	
						-0.5f, -0.5f, -0.5f,	
						-0.5f, -0.5f, 0.5f,	
						-0.5f, 0.5f, 0.5f,

						0.5f, 0.5f, -0.5f,	
						0.5f, -0.5f, -0.5f,	
						-0.5f, -0.5f, 0.5f,	
						-0.5f, 0.5f, 0.5f,	
						
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
	
	
	glGenVertexArrays(1,&VAO);
	glGenBuffers(1,&VBO);
	glBindVertexArray(VAO);
	

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

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

void display()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//	glBindVertexArray(VAO);
	//glDrawArrays(GL_TRIANGLES, 12, 24);
//	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
//	glBindVertexArray(0);

	g.draw();

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
	glViewport(0,0,width,height);
}

void setUpCallbacks()
{
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
}

