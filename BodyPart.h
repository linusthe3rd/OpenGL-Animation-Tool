/*
 *  BodyPart.h
 *  Project 2
 *
 *  A class that represents a body part of a robot.
 *
 */
#ifndef BODYPART_H
#define BODYPART_H

#if defined(__APPLE__) || defined(MACOSX)
	#include <OpenGL/gl.h>	
	#include <GLUT/glut.h>
	#include <OpenGL/glu.h>
#else
	#include <GL/gl.h>
	#include <GL/glut.h>
	#include <GL/glu.h>
#endif

#include <string>
#include <sstream>

using namespace std;

#include "Point3f.h"
#include "Volume.h"
#include "stb_image.h"

struct Image_t {
	int width, height, n;
	unsigned char *data;
};

struct Rotation_t {
	float x, y, z;
	
	Rotation_t(){
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
};

class BodyPart {
	
protected:
	Point3f location;
	Volume vol;
	GLfloat ambient[4], diffuse[4], specular[4], shine;
	Image_t textureImg;
	GLuint texture[1];
	Rotation_t rotations;
	string name;
	
	
public:
	BodyPart(float x, float y, float z, float width=1.0f, float height=1.0f, float depth=1.0f);
	
	void setLocation(float x, float y, float z);
	Point3f getLocation();
	
	void setVolume(float width, float height, float depth);
	Volume getVolume();
	
	void setAmbientLightColor(float r, float g, float b, float a);
	GLfloat* getAmbientLightColor();
	
	void setDiffuseLightColor(float r, float g, float b, float a);
	GLfloat* getDiffuseLightColor();
	
	void setSpecularLightColor(float r, float g, float b, float a);
	GLfloat* getSpecularLightColor();
	
	void setShininess(float value);
	GLfloat getShininess();
	
	void setTextureImg(char *filename);
	
	void rotate(float angle, float x, float y, float z);
	Rotation_t getRotation();
		
	void draw();
	
	void setLimbName(string _name);
	string toString();
};
#endif
