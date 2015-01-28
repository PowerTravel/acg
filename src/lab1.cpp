#include <GL/glew.h>
#include <GL/glut.h>
#include "testinc.h"
//#include <GL/gl.h>
//#include <GL/glu.h>
void initGLEW()
{
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
	//glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	initGLEW();
	//initShaders();

	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

	glutInitWindowSize(1280, 720);
	glutInitWindowPosition(10,10);
	glutCreateWindow("GLUT Viewer");

	glutDisplayFunc(display);

	glutMainLoop();

	return 0;
}
