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
#include "Camera.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define PAN_STATE 1
#define ZOOM_STATE 2
#define ROTATE_STATE 3

Camera cam;

int cameraState;
bool isDragging;
int prevX, prevY;

// angle of rotation for the camera direction
float angle=0.0;
// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f;
// XZ position of the camera
float x=0.0f,z=5.0f;
void drawSnowMan() {
	
	glColor3f(1.0f, 1.0f, 1.0f);
	
	// Draw Body
	glTranslatef(0.0f ,0.75f, 0.0f);
	glutSolidSphere(0.75f,20,20);
	
	// Draw Head
	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.25f,20,20);
	
	// Draw Eyes
	glPushMatrix();
	glColor3f(0.0f,0.0f,0.0f);
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.05f,10,10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f,10,10);
	glPopMatrix();
	
	// Draw Nose
	glColor3f(1.0f, 0.5f , 0.5f);
	glRotatef(0.0f,1.0f, 0.0f, 0.0f);
	glutSolidCone(0.08f,0.5f,10,2);
}

void display(void){
	// Clear Color and Depth Buffers
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(cam.origin.x, cam.origin.y, cam.origin.z,
			  cam.lookAt.x, cam.lookAt.y,  cam.lookAt.z,
			  cam.upVector.x, cam.upVector.y,  cam.upVector.z);
	
	// Draw ground
	glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_QUADS);
		glVertex3f(-100.0f, 0.0f, -100.0f);
		glVertex3f(-100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f, -100.0f);
	glEnd();
	
	// Draw 36 SnowMen
	for(int i = -3; i < 3; i++)
		for(int j=-3; j < 3; j++) {
			glPushMatrix();
			glTranslatef(i*10.0,0,j * 10.0);
			drawSnowMan();
			glPopMatrix();
		}
	
	glutSwapBuffers();
}

void changeSize(int w, int h) {
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);
	
	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);
	
	glMatrixMode(GL_MODELVIEW);
}

void onMouseCB(int button, int state, int x, int y) {
	if( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN ) {
		isDragging = true;
		prevX = x;
		prevY = y;
	} else if( button == GLUT_LEFT_BUTTON && state == GLUT_UP ) {
		isDragging = false;
	}
}

void onMouseDragCB(int x, int y){
	if (isDragging) {
		switch (cameraState) {
			case PAN_STATE:
				if (x > prevX) {
					cam.Turn(0.05f, 0, 1, 0);
				} else {
					cam.Turn(-0.05f, 0, 1, 0);
				}
				break;
			case ZOOM_STATE:
				if (y > prevY) {
					cam.zoom(0.05f);
				} else {
					cam.zoom(-0.05f);
				}
				break;
			case ROTATE_STATE:
				if (x > prevX) {
					cam.roll(0.1);
				} else {
					cam.roll(-0.1);
				}
				break;
			default:
				break;
		}
		
		prevX = x;
		prevY = y;
	}
}

void onKeyboardCB(unsigned char key, int x, int y) {
	if (key == 'z'){
		cameraState = ZOOM_STATE;
	} else if (key == 'r'){
		cameraState = ROTATE_STATE;
	} else if (key == 'p') {
		cameraState = PAN_STATE;
	}

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
	glutIdleFunc(display);
	glutReshapeFunc(changeSize);
	
	glutMouseFunc(onMouseCB); 
	glutMotionFunc(onMouseDragCB);
	glutKeyboardFunc(onKeyboardCB);
	
	glEnable(GL_DEPTH_TEST);
	
	cam.init(1.0f, 1.0f, 5.0f,  
			 0.0f, 1.0f, 0.0f,   
			 0, 1, 0);
	cameraState = PAN_STATE;
	isDragging = false;
}


int main (int argc, char * argv[]) {
    glutInit(&argc, argv);
	
	init();
	
	glutMainLoop();
    return 0;
}
