/**************************
 * CS 4204 - Homework 4
 *
 * A program that displays a 3D robot. This robot's pose can be changed
 * as well as the camera's position and orientation.
 *
 * author: John Ryding (jlr25)
 * date: 4/2/11
 **************************/

#if defined(__APPLE__) || defined(MACOSX)
	#include <OpenGL/gl.h>	
	#include <GLUT/glut.h>
	#include <OpenGL/glu.h>
#else
	#include <GL/gl.h>
	#include <GL/glut.h>
	#include <GL/glu.h>
#endif

#include <iostream>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600



GLfloat light_diffuse[] = {1.0, 0.0, 0.0, 1.0};  /* Red diffuse light. */
GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};  /* Infinite light location. */
GLfloat n[6][3] = {  /* Normals for the 6 faces of a cube. */
	{-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0},
	{0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, -1.0} };
GLint faces[6][4] = {  /* Vertex indices for the 6 faces of a cube. */
	{0, 1, 2, 3}, {3, 2, 6, 7}, {7, 6, 5, 4},
	{4, 5, 1, 0}, {5, 6, 2, 1}, {7, 4, 0, 3} };
GLfloat v[8][3];  /* Will be filled in with X,Y,Z vertexes. */



void drawCube(void)
{
	for (int i = 0; i < 6; i++) {
		glBegin(GL_QUADS);
		glNormal3fv(&n[i][0]);
			glVertex3fv(&v[faces[i][0]][0]);
			glVertex3fv(&v[faces[i][1]][0]);
			glVertex3fv(&v[faces[i][2]][0]);
			glVertex3fv(&v[faces[i][3]][0]);
		glEnd();
	}
}

void display(void){
	//glMatrixMode (GL_PROJECTION);
	//glLoadIdentity();
	//set coordinate system to use window coordinates for points
	//gluOrtho2D(0, 800, 0, 600);
	
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	
	//resets the color state of all the pixels in the window, use it to set the background color of the window
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); 
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	drawCube();
	
	glutSwapBuffers();
}

void onMouseCB(int button, int state, int x, int y) {
	if( button == GLUT_LEFT_BUTTON && state == GLUT_UP ) {
	
	}
	
	glutPostRedisplay();
}

/*===================
 * Initialization
 *===================*/

void init(){
	//initialize openGL and the window
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
	glutInitWindowPosition(0,0);
	glutInitWindowSize(SCREEN_WIDTH,SCREEN_HEIGHT);
	glutCreateWindow("CS4204 Homework 4 - A Roh-bit!");
	
	// set up the event callbacks
	glutDisplayFunc(display); 
	glutMouseFunc(onMouseCB); 
	
	
	
	v[0][0] = v[1][0] = v[2][0] = v[3][0] = -1;
	v[4][0] = v[5][0] = v[6][0] = v[7][0] = 1;
	v[0][1] = v[1][1] = v[4][1] = v[5][1] = -1;
	v[2][1] = v[3][1] = v[6][1] = v[7][1] = 1;
	v[0][2] = v[3][2] = v[4][2] = v[7][2] = 1;
	v[1][2] = v[2][2] = v[5][2] = v[6][2] = -1;
	
	/* Enable a single OpenGL light. */
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	
	/* Use depth buffering for hidden surface elimination. */
	glEnable(GL_DEPTH_TEST);
	
	/* Setup the view of the cube. */
	glMatrixMode(GL_PROJECTION);
	gluPerspective( /* field of view in degree */ 40.0,
				   /* aspect ratio */ 1.0,
				   /* Z near */ 1.0, /* Z far */ 10.0);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(0.0, 0.0, 5.0,  /* eye is at (0,0,5) */
			  0.0, 0.0, 0.0,      /* center is at (0,0,0) */
			  0.0, 1.0, 0.);      /* up is in positive Y direction */
	
	/* Adjust cube position to be asthetic angle. */
	glTranslatef(0.0, 0.0, -1.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	glRotatef(-20, 0.0, 0.0, 1.0);
}


int main (int argc, char * argv[]) {
    glutInit(&argc, argv);
	
	init();
	
	glutMainLoop();
    return 0;
}
