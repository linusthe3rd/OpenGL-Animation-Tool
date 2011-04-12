/**************************
 * CS 4204 - Project 2
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
#include "Robot.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define PAN_STATE 1
#define ZOOM_STATE 2
#define ROTATE_STATE 3
#define EDIT_STATE 4

#define X_AXIS 1
#define Y_AXIS 2
#define Z_AXIS 3

#define ZERO -1
#define HEAD 0
#define UPPER_TORSO 1
#define LOWER_TORSO 2
#define UPPER_LEFT_ARM 3
#define	LOWER_LEFT_ARM 4
#define LEFT_HAND 5
#define UPPER_RIGHT_ARM 6
#define LOWER_RIGHT_ARM 7
#define RIGHT_HAND 8
#define UPPER_LEFT_LEG 9
#define LOWER_LEFT_LEG 10
#define LEFT_FOOT 11
#define UPPER_RIGHT_LEG 12
#define LOWER_RIGHT_LEG 13
#define RIGHT_FOOT 14


Camera cam;
int cameraState, axisState;
bool isDragging;
int prevX, prevY;

Robot *robot;

void display(void){
	// Clear Color and Depth Buffers
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(cam.origin.x, cam.origin.y, cam.origin.z,
			  cam.lookAt.x, cam.lookAt.y,  cam.lookAt.z,
			  cam.upVector.x, cam.upVector.y,  cam.upVector.z);
	
	// Draw floor
	GLfloat ambient[] = {0.9f, 0.9f, 0.9f, 1.0};
	GLfloat diffuse[] = {0.9f, 0.9f, 0.9f, 1.0};
	GLfloat specular[] = {0.9f, 0.9f, 0.9f, 1.0};
	GLfloat shine = 100.0;
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT, GL_SHININESS, shine);
	
	glBegin(GL_QUADS);
		glVertex3f(-100.0f, 0.0f, -100.0f);
		glVertex3f(-100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f, -100.0f);
	glEnd();
	
	//draw robot
	robot->draw();
	
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
		float rotateAngle = 0.0;
		
		switch (cameraState) {
			case PAN_STATE:
				if (x > prevX) {
					cam.turn(0.05f, 0, 1, 0);
				} else {
					cam.turn(-0.05f, 0, 1, 0);
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
			case EDIT_STATE:
				if (x > prevX) {
					rotateAngle = 10.0;
				} else {
					rotateAngle = -10.0;
				}
				
				switch (axisState) {
					case X_AXIS:
						robot->rotateLimb(rotateAngle, 1.0, 0.0, 0.0);
						break;
					case Y_AXIS:
						robot->rotateLimb(rotateAngle, 0.0, 1.0, 0.0);
						break;
					case Z_AXIS:
						robot->rotateLimb(rotateAngle, 0.0, 0.0, 1.0);
						break;
					default:
						break;
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
	} else if (key == 'e') {
		cameraState = EDIT_STATE;
	} else if (key == '1') {
		axisState = X_AXIS;
	} else if (key == '2') {
		axisState = Y_AXIS;
	} else if (key == '3') {
		axisState = Z_AXIS;
	}

}

void onContextMenuCB(int option){
	robot->setEditableLimb(option);
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
	
	glutCreateMenu(onContextMenuCB);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutAddMenuEntry("Head", HEAD);
	glutAddMenuEntry("", ZERO);
	glutAddMenuEntry("Upper Torso", UPPER_TORSO);
	glutAddMenuEntry("Lower Torso", LOWER_TORSO);
	glutAddMenuEntry("", ZERO);
	glutAddMenuEntry("Upper Left Arm", UPPER_LEFT_ARM);
	glutAddMenuEntry("Lower Left Arm", LOWER_LEFT_ARM);
	glutAddMenuEntry("Left Hand", LEFT_HAND);
	glutAddMenuEntry("", ZERO);
	glutAddMenuEntry("Upper Right Arm", UPPER_RIGHT_ARM);
	glutAddMenuEntry("Lower Right Arm", LOWER_RIGHT_ARM);
	glutAddMenuEntry("Right Hand", RIGHT_HAND);
	glutAddMenuEntry("", ZERO);
	glutAddMenuEntry("Upper Left Leg", UPPER_LEFT_LEG);
	glutAddMenuEntry("Lower Left Leg", LOWER_LEFT_LEG);
	glutAddMenuEntry("Left Leg", LEFT_FOOT);
	glutAddMenuEntry("", ZERO);
	glutAddMenuEntry("Upper Right Leg", UPPER_RIGHT_LEG);
	glutAddMenuEntry("Lower Right Leg", LOWER_RIGHT_LEG);
	glutAddMenuEntry("Right Foot", RIGHT_FOOT);
	
	glEnable(GL_DEPTH_TEST);
	
	glEnable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
	
	glEnable(GL_TEXTURE_2D);
	
	cam.init(2.0f, 1.0f, 5.0f,  
			 0.0f, 1.0f, 0.0f,   
			 0, 1, 0);
	cameraState = PAN_STATE;
	axisState = X_AXIS;
	isDragging = false;
	
	robot = new Robot();
}


int main (int argc, char * argv[]) {
    glutInit(&argc, argv);
	
	init();
	
	glutMainLoop();
    return 0;
}
