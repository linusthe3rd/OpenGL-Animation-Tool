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

void Camera::turn(float angle, float x, float y, float z){
	// Store the new focus point
	Point3f newFocus;
	
	Point3f view;
	view.x = this->lookAt.x - this->origin.x;
	view.y = this->lookAt.y - this->origin.y;
	view.z = this->lookAt.z - this->origin.z;
	
	// Calculate the sine and cosine of the angle once
	float cosTheta = (float)cos(angle);
	float sinTheta = (float)sin(angle);
	
	// Find the new x position for the new rotated point
	newFocus.x = (cosTheta + (1 - cosTheta) * x * x)* view.x;
	newFocus.x += ((1 - cosTheta) * x * y - z * sinTheta)* view.y;
	newFocus.x += ((1 - cosTheta) * x * z + y * sinTheta)* view.z;
	
	// Find the new y position for the new rotated point
	newFocus.y = ((1 - cosTheta) * x * y + z * sinTheta)* view.x;
	newFocus.y += (cosTheta + (1 - cosTheta) * y * y)* view.y;
	newFocus.y += ((1 - cosTheta) * y * z - x * sinTheta)* view.z;
	
	// Find the new z position for the new rotated point
	newFocus.z = ((1 - cosTheta) * x * z - y * sinTheta)* view.x;
	newFocus.z += ((1 - cosTheta) * y * z + x * sinTheta)* view.y;
	newFocus.z += (cosTheta + (1 - cosTheta) * z * z)* view.z;
	
	this->lookAt.x = this->origin.x + newFocus.x;
	this->lookAt.y = this->origin.y + newFocus.y;
	this->lookAt.z = this->origin.z + newFocus.z; 
}

void Camera::roll(float angle){
	this->upVector.x = cos(angle) * this->upVector.x + sin(angle) * this->upVector.y;
	this->upVector.y = -sin(angle) * this->upVector.x + cos(angle) * this->upVector.y;
}

void Camera::zoom(float amount){
	Point3f view;
	view.x = this->lookAt.x - this->origin.x;
	view.y = this->lookAt.y - this->origin.y;
	view.z = this->lookAt.z - this->origin.z;
	
	this->origin.x += view.x * amount;
	this->origin.z += view.z * amount;
	
	this->lookAt.x += view.x * amount;
	this->lookAt.z += view.z * amount;
}