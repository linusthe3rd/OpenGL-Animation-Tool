#include "BodyPart.h"

/**
 * Create a new body part with a position and volume
 */
BodyPart::BodyPart(float x, float y, float z, float width, float height, float depth)  {
	this->location = Point3f(x, y, z);
	this->vol = Volume(width, height, depth);
	this->rotations = Rotation_t();
	
	this->ambient[0] = 0.9;  
	this->ambient[1] = 0.9;
	this->ambient[2] = 0.9;
	this->ambient[3] = 1.0;
	
	this->diffuse[0] = 0.9;  
	this->diffuse[1] = 0.9;
	this->diffuse[2] = 0.9;
	this->diffuse[3] = 1.0;
	
	this->specular[0] = 0.9;  
	this->specular[1] = 0.9;
	this->specular[2] = 0.9;
	this->specular[3] = 1.0;
	
	this->shine = 100.0f;
	
	this->name = "";
}

/**
 * Set the location of the body part.
 */
void BodyPart::setLocation(float x, float y, float z){
	this->location.x = x;
	this->location.y = y;
	this->location.z = z;
}

/**
 * Get the location of the body part.
 */
Point3f BodyPart::getLocation(){
	return this->location;
}

/**
 * Set the volume of the body part.
 */
void BodyPart::setVolume(float width, float height, float depth){
	this->vol.w = width;
	this->vol.h = height;
	this->vol.d = depth;
}

/**
 * Get the volume of the body part.
 */
Volume BodyPart::getVolume(){
	return this->vol;
}

/**
 * Set the ambient lighting value of the body part.
 */
void BodyPart::setAmbientLightColor(float r, float g, float b, float a){
	this->ambient[0] = r;
	this->ambient[1] = g;
	this->ambient[2] = b;
	this->ambient[3] = a;
}

/**
 * Get the ambient lighting value of the body part.
 */
GLfloat* BodyPart::getAmbientLightColor(){
	return this->ambient;
}

/**
 * Set the diffuse lighting value of the body part.
 */
void BodyPart::setDiffuseLightColor(float r, float g, float b, float a){
	this->diffuse[0] = r;
	this->diffuse[1] = g;
	this->diffuse[2] = b;
	this->diffuse[3] = a;
}

/**
 * Get the diffuse lighting value of the body part.
 */
GLfloat* BodyPart::getDiffuseLightColor(){
	return this->diffuse;
}

/**
 * Set the specular lighting value of the body part.
 */
void BodyPart::setSpecularLightColor(float r, float g, float b, float a){
	this->specular[0] = r;
	this->specular[1] = g;
	this->specular[2] = b;
	this->specular[3] = a;
}

/**
 * Get the specular lighting value of the body part.
 */
GLfloat* BodyPart::getSpecularLightColor(){
	return this->specular;
}

/**
 * Set the shininess value of the body part.
 */
void BodyPart::setShininess(float value){
	this->shine = value;
}

/**
 * Get the shininess value of the body part.
 */
GLfloat BodyPart::getShininess(){
	return this->shine;
}

/**
 * Set the texture the body part should use in rendering.
 *
 * Params
 *	filename - the path to the image file that will be used as the texture.
 */
void BodyPart::setTextureImg(char *filename){
	this->textureImg.data = stbi_load(filename, &this->textureImg.width, &this->textureImg.height, &this->textureImg.n, 0);
	
	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexImage2D(GL_TEXTURE_2D,0,3,this->textureImg.width,this->textureImg.height,0,GL_RGB,GL_UNSIGNED_BYTE,this->textureImg.data);
}

/**
 * Add a rotation transformation to the body part's position.
 *
 * Params
 *	angle - the amount to rotate
 *	x - the x-axis, should be 0 or 1
 *	y - the y-axis, should be 0 or 1
 *	z - the z-axis, should be 0 or 1
 */
void BodyPart::rotate(float angle, float x, float y, float z){
	if (x == 1.0) {
		this->rotations.x += angle;
	} else if (y == 1.0) {
		this->rotations.y += angle;
	} else if (z == 1.0) {
		this->rotations.z += angle;
	}
}

Rotation_t BodyPart::getRotation(){
	return this->rotations;
}

/**
 * Draw the body part in the window.
 */
void BodyPart::draw(){
	GLfloat minX = this->location.x - ( this->vol.w / 2 );
	GLfloat maxX = this->location.x + ( this->vol.w / 2 );
	
	GLfloat maxY = this->location.y;
	GLfloat minY = this->location.y - this->vol.h;
	
	GLfloat minZ = this->location.z - ( this->vol.d / 2 );
	GLfloat maxZ = this->location.z + ( this->vol.d / 2 );
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, this->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, this->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, this->specular);
	glMaterialf(GL_FRONT, GL_SHININESS, this->shine);
	
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
	
	glTranslatef(this->location.x, this->location.y, this->location.z);
	glRotatef(this->rotations.x, 1.0, 0.0, 0.0);
	glRotatef(this->rotations.y, 0.0, 1.0, 0.0);
	glRotatef(this->rotations.z, 0.0, 0.0, 1.0);
	glTranslatef(-this->location.x, -this->location.y, -this->location.z);
	
	glBegin(GL_QUADS);
		//Draw top and bottom faces
		glNormal3f(0, 1.0f, 0);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( minX, minY, minZ);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( minX, minY, maxZ);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( maxX, minY, maxZ);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( maxX, minY, minZ);
		
		glNormal3f(0, -1.0f, 0);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( minX, maxY, minZ);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( minX, maxY, maxZ);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( maxX, maxY, maxZ);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( maxX, maxY, minZ);
	
		//draw left and right face
		glNormal3f(-1.0f, 0, 0);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( minX, minY, minZ);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( minX, minY, maxZ);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( minX, maxY, maxZ);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( minX, maxY, minZ);
	
		glNormal3f(1.0f, 0, 0);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( maxX, minY, minZ);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( maxX, minY, maxZ);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( maxX, maxY, maxZ);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( maxX, maxY, minZ);
	
		//draw front and back faces
		glNormal3f(0, 0, 1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( minX, minY, maxZ);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( minX, maxY, maxZ);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( maxX, maxY, maxZ);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( maxX, minY, maxZ);
		
		glNormal3f(0, 0, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( minX, minY, minZ);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( minX, maxY, minZ);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( maxX, maxY, minZ);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( maxX, minY, minZ);
	glEnd();
}

void BodyPart::setLimbName(string _name){
	this->name = _name;
}

string BodyPart::toString(){
	ostringstream oss;
	
	oss << this->name << "\r\n";
	oss << "Texture Name\r\n";
	oss << this->rotations.x << " " << this->rotations.y << " " << this->rotations.z << "\r\n";
	oss << this->ambient[0] << " " << this->ambient[1] << " " << this->ambient[2] << " " << this->ambient[3] << "\r\n";
	oss << this->diffuse[0] << " " << this->diffuse[1] << " " << this->diffuse[2] << " " << this->diffuse[3] << "\r\n";
	oss << this->specular[0] << " " << this->specular[1] << " " << this->specular[2] << " " << this->specular[3] << "\r\n";
	oss << this->shine << "\r\n";
	oss << "\r\n";
	
	return oss.str();
}