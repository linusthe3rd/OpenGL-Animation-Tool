/*
 *  Camera.h
 *  Homework4
 *
 *  Created by John Ryding on 4/2/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef CAMERA_H
#define CAMERA_H

#include "Point3f.h"

class Camera {
public:
	Point3f origin;
	Point3f lookAt;
	Point3f panAmount;
	Point3f upVector;
	
	Camera();
	
	void init(float xOrigin, float yOrigin, float zOrigin,
		   float xLookAt, float yLookAt, float zLookAt,
		   float xUpVector, float yUpVector, float zUpVector);
	
	void setOrigin(float x, float y, float z);
	void setLookAt(float x, float y, float z);
	void setUpVector(float x, float y, float z);
	void pan(float angle);
	void zoom(float amount);
};

#endif