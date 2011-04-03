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
	this->deltaAmt = Point3f(0.0f, 0.0f, -1.0f);
	
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

void Camera::pan(float angle){
	this->deltaAmt.x += sin(angle);
	this->deltaAmt.z += -cos(angle);
}

void Camera::pan(int newX, int newY){
	int v[3] = { 
		this->lookAt.x - this->origin.x,
		this->lookAt.y - this->origin.y,
		this->lookAt.z - this->origin.z
	};
	
	int q[3] = { 
		newX - this->origin.x,
		this->lookAt.y - this->origin.y,
		this->lookAt.z - this->origin.z
	};
	
	float mags = magnitude(v) * magnitude(q);
	float value = dotProduct(v, q) / mags;
	float angle = acos(value);
	
	this->pan(angle);
}

void Camera::zoom(float amount){
	this->origin.x += this->deltaAmt.x * amount;
	this->lookAt.x += this->deltaAmt.x * amount;
	this->origin.z += this->deltaAmt.z * amount;
	this->lookAt.z += this->deltaAmt.z * amount;
}