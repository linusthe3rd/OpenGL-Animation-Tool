/*
 *  BodyPart.cpp
 *  Homework4
 *
 *  Created by John Ryding on 4/3/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "BodyPart.h"

BodyPart::BodyPart(float x, float y, float z, float width, float height, float depth){
	this->location = Point3f(x, y, z);
	this->vol = Volume(width, height, depth);
}

void BodyPart::setLocation(float x, float y, float z){
	this->location.x = x;
	this->location.y = y;
	this->location.z = z;
}

Point3f BodyPart::getLocation(){
	return this->location;
}

void BodyPart::setVolume(float width, float height, float depth){
	this->vol.w = width;
	this->vol.h = height;
	this->vol.d = depth;
}

Volume BodyPart::getVolume(){
	return this->vol;
}

bool BodyPart::contains(int x, int y){
	return false;
}

void BodyPart::draw(){
	GLfloat minX = this->location.x - ( this->vol.w / 2 );
	GLfloat maxX = this->location.x + ( this->vol.w / 2 );
	
	GLfloat minY = this->location.y;
	GLfloat maxY = this->location.y + this->vol.h;
	
	GLfloat minZ = this->location.z - ( this->vol.d / 2 );
	GLfloat maxZ = this->location.z + ( this->vol.d / 2 );
	
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
		//Draw top and bottom faces
		glVertex3f( minX, minY, minZ);
		glVertex3f( minX, minY, maxZ);
		glVertex3f( maxX, minY, maxZ);
		glVertex3f( maxX, minY, minZ);
	
		glVertex3f( minX, maxY, minZ);
		glVertex3f( minX, maxY, maxZ);
		glVertex3f( maxX, maxY, maxZ);
		glVertex3f( maxX, maxY, minZ);
	
		//draw left and right face
		glVertex3f( minX, minY, minZ);
		glVertex3f( minX, minY, maxZ);
		glVertex3f( minX, maxY, maxZ);
		glVertex3f( minX, maxY, minZ);
	
		glVertex3f( maxX, minY, minZ);
		glVertex3f( maxX, minY, maxZ);
		glVertex3f( maxX, maxY, maxZ);
		glVertex3f( maxX, maxY, minZ);
	
		//draw front and back faces
		glVertex3f( minX, minY, minZ);
		glVertex3f( minX, maxY, minZ);
		glVertex3f( maxX, maxY, minZ);
		glVertex3f( maxX, minY, minZ);
	
		glVertex3f( minX, minY, maxZ);
		glVertex3f( minX, maxY, maxZ);
		glVertex3f( maxX, maxY, maxZ);
		glVertex3f( maxX, minY, maxZ);
	glEnd();
}