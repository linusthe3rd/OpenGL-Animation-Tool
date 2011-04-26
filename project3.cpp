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
#include <fstream>
#include <cstring>
#include <cerrno>

#include "Player.h"
#include "Camera.h"
#include "Robot.h"

#define SPACEBAR 32

#define TIMERMSECS 33

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define PAN_STATE 1
#define ZOOM_STATE 2
#define ROTATE_STATE 3
#define EDIT_STATE 4

#define X_AXIS 1
#define Y_AXIS 2
#define Z_AXIS 3

#define FRAMERATE_10 1000
#define FRAMERATE_20 200
#define FRAMERATE_30 300
#define FRAMERATE_40 400
#define FRAMERATE_50 500
#define FRAMERATE_60 600

#define ZERO -1
#define SAVE_BTN 100
#define SAVE_ANIMATION_BTN 101
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

#define ADD_KEYFRAME 20



Camera cam;
int cameraState, axisState;
bool isDragging, isShiftDown, isPlaying, isForward;
int prevX, prevY;
char* loadFileName;
char* saveFileName;
char* loadAnimFileName;
char* saveAnimFileName;
char frameText[100];
Robot *robot;
Player *player;

int currentFrame, framerate;
bool isKeyframe;


void renderBitmapString(
						float x,
						float y,
						float z,
						void *font,
						char *string) {
	
	char *c;
	glRasterPos3f(x, y,z);
	for (c=string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}

void updateFrameText(){
	if (currentFrame < 0) {
		isKeyframe = true;
		currentFrame *= -1;
	} else {
		isKeyframe = false;
	}

	sprintf(frameText, "Frame: %d", currentFrame);
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
	
	glDisable (GL_LIGHTING);
    glDisable (GL_LIGHT0);
	
	if (isKeyframe) {
		glColor3f(0.0f, 1.0f, 0.0f);
	} else {
		glColor3f(1.0f, 1.0f, 1.0f);
	}

	renderBitmapString(1.0f, 2.5f, 0.0f, GLUT_BITMAP_HELVETICA_18, frameText);
	//renderBitmapString(1.0f, 2.5f, 0.0f, GLUT_BITMAP_HELVETICA_18, "Framerate: 1");
	
	glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
	
	// Draw floor
	GLfloat ambient[] = {0.5f, 0.9f, 0.9f, 1.0};
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

void animate(int value) {
	int timerMS = int(( 1.0 / framerate ) * 1000);
	glutTimerFunc(timerMS, animate, 0);
	
	if (isPlaying) {
		if (isForward) {
			player->incrementFrame(&currentFrame);
			updateFrameText();
		} else {
			player->decrementFrame(&currentFrame);
			updateFrameText();
		}
		
		glutPostRedisplay();
	}
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
		isShiftDown = (glutGetModifiers() == GLUT_ACTIVE_SHIFT);
		isDragging = true;
		prevX = x;
		prevY = y;
	} else if( button == GLUT_LEFT_BUTTON && state == GLUT_UP ) {
		isDragging = false;
	}
	
	glutPostRedisplay();
}

void onMouseDragCB(int x, int y){
	if (isDragging) {
		float rotateAngle = 0.0;	
		if (isShiftDown){
			if (x > prevX) {
				player->incrementFrame(&currentFrame);
				updateFrameText();
			} else {
				player->decrementFrame(&currentFrame);
				updateFrameText();
			}
		} else {
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
			
		}

		prevX = x;
		prevY = y;
	}
	
	glutPostRedisplay();
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
	} else if (key == 'f') {
		isPlaying = true;
		isForward = true;
	} else if (key == 'b') {
		isPlaying = true;
		isForward = false;
	} else if (key == 's') {
		isPlaying = false;
	} else if (key == SPACEBAR) {
		player->addKeyFrame();
	}
}

void onSpecialKeyboardCB(int key, int x, int y) { 
	switch (key) {
		case GLUT_KEY_LEFT:
			player->decrementFrame(&currentFrame);
			updateFrameText();
			glutPostRedisplay();
			break;
		case GLUT_KEY_RIGHT:
			player->incrementFrame(&currentFrame);
			updateFrameText();
			glutPostRedisplay();
			break;
		default:
			break;
	}
	
	
}

void saveCurrentPose(){
	char* fName = NULL;
	if (saveFileName != NULL ) {
		fName = saveFileName;
	} else if (loadFileName != NULL){
		fName = loadFileName;
	}
	
	if (fName != NULL){
		remove(fName);
		ofstream fout(fName);
		
		if (fout) {
			fout << robot->toString();
			fout.close();
		} else {
			cout << "Unable to write " << saveFileName << endl;
		}
	}
}

void saveCurrentAnimation(){
	char* fName = NULL;
	if (saveAnimFileName != NULL ) {
		fName = saveAnimFileName;
	} else if (loadAnimFileName != NULL){
		fName = loadAnimFileName;
	}
	
	if (fName != NULL){
		remove(fName);
		ofstream fout(fName);
		
		if (fout) {
			fout << player->toString();
			fout.close();
		} else {
			cout << "Unable to write " << saveFileName << endl;
		}
	}
}

void onContextMenuCB(int option){
	if (option == SAVE_BTN) {
		saveCurrentPose();
	} else if (option == SAVE_ANIMATION_BTN) {
		saveCurrentAnimation();
	} else if (option == ADD_KEYFRAME) {
		player->addKeyFrame();
	} else if (option == FRAMERATE_10){
		framerate = 10;
	} else if (option == FRAMERATE_20){
		framerate = 20;
	} else if (option == FRAMERATE_30){
		framerate = 30;
	} else if (option == FRAMERATE_40){
		framerate = 40;
	} else if (option == FRAMERATE_50){
		framerate = 50;
	} else if (option == FRAMERATE_60){
		framerate = 60;
	} else {
		robot->setEditableLimb(option);
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
	
	int timerMS = int(( 1.0 / 30 ) * 1000);
	glutTimerFunc(timerMS, animate, 0);
	glutReshapeFunc(changeSize);
	
	glutMouseFunc(onMouseCB); 
	glutMotionFunc(onMouseDragCB);
	glutKeyboardFunc(onKeyboardCB);
	glutSpecialFunc(onSpecialKeyboardCB); 
	
	int frMenu = glutCreateMenu(onContextMenuCB);
	glutAddMenuEntry("10",FRAMERATE_10);
	glutAddMenuEntry("20",FRAMERATE_20);
	glutAddMenuEntry("30",FRAMERATE_30);
	glutAddMenuEntry("40",FRAMERATE_40);
	glutAddMenuEntry("50",FRAMERATE_50);
	glutAddMenuEntry("60",FRAMERATE_60);
	
	
	glutCreateMenu(onContextMenuCB);
	glutAddSubMenu("Set Framerate", frMenu);
	
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	if (saveFileName != NULL || loadFileName != NULL) {
		glutAddMenuEntry("Save Pose", SAVE_BTN);
	}
	
	if (saveAnimFileName != NULL || loadAnimFileName != NULL) {
		glutAddMenuEntry("Save Animation", SAVE_ANIMATION_BTN);
	}
	
	glutAddMenuEntry("", ZERO);
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
	isShiftDown = false;
	
	robot = new Robot();
	player = new Player(robot);
	isPlaying = false;
	isForward = true;
	currentFrame = 0;
	framerate = 30;
	updateFrameText();
	
	if (loadFileName != NULL) {
		robot->loadPose(loadFileName);
	}
	
	if (loadAnimFileName != NULL) {
		player->loadAnim(loadAnimFileName);
	}
}


int main (int argc, char * argv[]) {
	char* arg;
	for (int i = 0; i < argc; i++) {
		arg = argv[i];
		
		if (strcmp(arg, "-s") == 0) {
			saveFileName = argv[i+1];
		} else if (strcmp(arg, "-l") == 0) {
			loadFileName = argv[i+1];
		} else if (strcmp(arg, "-As") == 0) {
			saveAnimFileName = argv[i+1];
		} else if (strcmp(arg, "-Al") == 0) {
			loadAnimFileName = argv[i+1];
		}
	}
	
	
    glutInit(&argc, argv);
	
	init();
	
	glutMainLoop();
    return 0;
}
