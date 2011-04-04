/*
 *  BodyPart.h
 *  Homework4
 *
 *  Created by John Ryding on 4/3/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
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

#include "Point3f.h"
#include "Volume.h"

class BodyPart {
	
protected:
	Point3f location;
	Volume vol;

public:
	BodyPart(float x, float y, float z, float width=1.0f, float height=1.0f, float depth=1.0f);
	
	void setLocation(float x, float y, float z);
	Point3f getLocation();
	
	void setVolume(float width, float height, float depth);
	Volume getVolume();
	
	bool contains(int x, int y);	
	
	void draw();
};
#endif
