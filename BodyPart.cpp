/*
 *  BodyPart.cpp
 *  Homework4
 *
 *  Created by John Ryding on 4/3/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "BodyPart.h"

BodyPart::BodyPart(float x, float y, float z, float width, float height, float depth)  {
	this->location = Point3f(x, y, z);
	this->vol = Volume(width, height, depth);
	
	this->ambient[0] = 0.2;  
	this->ambient[1] = 0.2;
	this->ambient[2] = 0.2;
	this->ambient[3] = 1.0;
	
	this->diffuse[0] = 1.0;  
	this->diffuse[1] = 0.8;
	this->diffuse[2] = 0.0;
	this->diffuse[3] = 1.0;
	
	this->specular[0] = 1.0;  
	this->specular[1] = 1.0;
	this->specular[2] = 1.0;
	this->specular[3] = 1.0;
	
	this->shine = 100.0f;
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

void BodyPart::setAmbientLightColor(float r, float g, float b, float a){
	this->ambient[0] = r;
	this->ambient[1] = g;
	this->ambient[2] = b;
	this->ambient[3] = a;
}

GLfloat* BodyPart::getAmbientLightColor(){
	return this->ambient;
}

void BodyPart::setDiffuseLightColor(float r, float g, float b, float a){
	this->diffuse[0] = r;
	this->diffuse[1] = g;
	this->diffuse[2] = b;
	this->diffuse[3] = a;
}

GLfloat* BodyPart::getDiffuseLightColor(){
	return this->diffuse;
}

void BodyPart::setSpecularLightColor(float r, float g, float b, float a){
	this->specular[0] = r;
	this->specular[1] = g;
	this->specular[2] = b;
	this->specular[3] = a;
}

GLfloat* BodyPart::getSpecularLightColor(){
	return this->specular;
}

void BodyPart::setShininess(float value){
	this->shine = value;
}

GLfloat BodyPart::getShininess(){
	return this->shine;
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
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, this->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, this->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, this->specular);
	glMaterialf(GL_FRONT, GL_SHININESS, this->shine);
	
	glBegin(GL_QUADS);
		//Draw top and bottom faces
		glNormal3f(0, 1.0f, 0);
		glVertex3f( minX, minY, minZ);
		glVertex3f( minX, minY, maxZ);
		glVertex3f( maxX, minY, maxZ);
		glVertex3f( maxX, minY, minZ);
		
		glNormal3f(0, -1.0f, 0);
		glVertex3f( minX, maxY, minZ);
		glVertex3f( minX, maxY, maxZ);
		glVertex3f( maxX, maxY, maxZ);
		glVertex3f( maxX, maxY, minZ);
	
		//draw left and right face
		glNormal3f(-1.0f, 0, 0);
		glVertex3f( minX, minY, minZ);
		glVertex3f( minX, minY, maxZ);
		glVertex3f( minX, maxY, maxZ);
		glVertex3f( minX, maxY, minZ);
	
		glNormal3f(1.0f, 0, 0);
		glVertex3f( maxX, minY, minZ);
		glVertex3f( maxX, minY, maxZ);
		glVertex3f( maxX, maxY, maxZ);
		glVertex3f( maxX, maxY, minZ);
	
		//draw front and back faces
		glNormal3f(0, 0, -1.0f);
		glVertex3f( minX, minY, minZ);
		glVertex3f( minX, maxY, minZ);
		glVertex3f( maxX, maxY, minZ);
		glVertex3f( maxX, minY, minZ);
	
		glNormal3f(0, 0, 1.0f);
		glVertex3f( minX, minY, maxZ);
		glVertex3f( minX, maxY, maxZ);
		glVertex3f( maxX, maxY, maxZ);
		glVertex3f( maxX, minY, maxZ);
	glEnd();
}