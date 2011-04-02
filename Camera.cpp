/*
 *  Camera.cpp
 *  Homework4
 *
 *  Created by John Ryding on 4/2/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Camera.h"

Camera::Camera(){
	init(0, 0, 0,
		 0, 0, 0,
		 0, 1, 0);
}

void Camera::init(float xOrigin, float yOrigin, float zOrigin,
				  float xLookAt, float yLookAt, float zLookAt,
				  float xUpVector, float yUpVector, float zUpVector){
	this->origin = Point3f(xOrigin, yOrigin, zOrigin);
	this->lookAt = Point3f(xLookAt, yLookAt, zLookAt);
	this->upVector = Point3f(xUpVector, yUpVector, zUpVector);
	
}

void Camera::setOrigin(float x, float y, float z){
	this->origin.x = x;
	this->origin.y = y;
	this->origin.z = z;
}
void Camera::setLookAt(float x, float y, float z){
	this->lookAt.x = x;
	this->lookAt.y = y;
	this->lookAt.z = z;
}
void Camera::setUpVector(float x, float y, float z){
	this->upVector.x = x;
	this->upVector.y = y;
	this->upVector.z = z;
}