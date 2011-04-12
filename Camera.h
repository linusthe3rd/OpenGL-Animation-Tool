/*
 *  Camera.h
 *  Project 2
 *
 *  Class that abstracts the underlying processing
 *  of a camera's position in a 3D environment.
 *
 */
#ifndef CAMERA_H
#define CAMERA_H

#include "Point3f.h"
#include "VectorsUtil.h"

class Camera {
public:
	Point3f origin;
	Point3f lookAt;
	Point3f upVector;
	
	Camera();
	
	void init(float xOrigin, float yOrigin, float zOrigin,
		   float xLookAt, float yLookAt, float zLookAt,
		   float xUpVector, float yUpVector, float zUpVector);
	
	void setOrigin(float x, float y, float z);
	void setLookAt(float x, float y, float z);
	void setUpVector(float x, float y, float z);
	void turn(float angle, float x, float y, float z);  
	void roll(float angle);
	void zoom(float amount);
};

#endif