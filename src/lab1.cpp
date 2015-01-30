#include <GL/glew.h>
//#include <GL/glut.h>
//#include <GL/gl.h>
//#include <GL/glu.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#include "ShaderTools.hpp"

#include <iostream>


char V_SHADER[] = "shaders/vshader.glsl";
char F_SHADER[] = "shaders/fshader.glsl";

void setUpGlut(int argc, char* argv[])
{
	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

//	glutInitContextVersion(3,0);
//	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
//	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutInitWindowSize(1280, 720);
	glutInitWindowPosition(10,10);
	glutCreateWindow("GLUT Viewer");
}

void setUpGlew(){

	glewInit();

	if(	glewGetExtension("GL_ARB_fragment_shader") != GL_TRUE ||
		glewGetExtension("GL_ARB_vertex_shader") != GL_TRUE ||
		glewGetExtension("GL_ARB_shader_objects") != GL_TRUE ||
		glewGetExtension("GL_ARB_shading_language_100") != GL_TRUE  )
	{
		std::cerr << "Driver does not support OpenGL shading language" << std::endl;
		exit(1);
	}
}

void display()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glutSwapBuffers();
	glutPostRedisplay();
}

void setUpCallbacks()
{
	glutDisplayFunc(display);
}

int main(int argc, char* argv[])
{

	// Set up glut and glew
	setUpGlut(argc, argv);
	setUpGlew();
	// Load Shaders, Add so that you get back a struct with the program id and the shader ids
	initProgram("shaders/vshader.glsl", "shaders/fshader.glsl");
	
	// Load Objects here

	setUpCallbacks();

	glutMainLoop();

	return 0;
}
