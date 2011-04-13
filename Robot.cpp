#include "Robot.h"

#define HEAD 0
#define UPPER_TORSO 1
#define LOWER_TORSO 2
#define UPPER_LEFT_ARM 3
#define	LOWER_LEFT_ARM 4
#define LEFT_HAND 5
#define UPPER_RIGHT_ARM 6
#define LOWER_RIGHT_ARM 7
#define RIGHT_HAND 8
#define UPPER_LEFT_LEG 9
#define LOWER_LEFT_LEG 10
#define LEFT_FOOT 11
#define UPPER_RIGHT_LEG 12
#define LOWER_RIGHT_LEG 13
#define RIGHT_FOOT 14

/**
 * Create a new robot. This will initialize all of the body parts
 * that the robot will have.s
 */
Robot::Robot(){
	this->head = new BodyPart("head", 0.0f, 2.5f, 0.0f, 0.5f, 0.5f, 0.5f);
	this->head->setTextureImg("Baboon.bmp");
	
	this->upperTorso = new BodyPart("upperTorso", 0.0f, 2.0f, 0.0f, 1.0f, 0.5f, 1.0f);
	this->lowerTorso = new BodyPart("lowerTorso", 0.0f, 1.5f, 0.0f, 1.0f, 0.5f, 1.0f);
	
	this->upperTorso->setTextureImg("color_rows.bmp");
	this->upperTorso->setAmbientLightColor(1.0f, 0.0f, 0.0f, 1.0f);
	this->upperTorso->setDiffuseLightColor(1.0f, 0.0f, 0.0f, 1.0f);
	this->upperTorso->setSpecularLightColor(1.0f, 0.0f, 0.0f, 1.0f);
	
	this->lowerTorso->setTextureImg("color_rows.bmp");
	this->lowerTorso->setAmbientLightColor(1.0f, 0.0f, 0.0f, 1.0f);
	this->lowerTorso->setDiffuseLightColor(1.0f, 0.0f, 0.0f, 1.0f);
	this->lowerTorso->setSpecularLightColor(1.0f, 0.0f, 0.0f, 1.0f);
	
	this->rUpperArm = new BodyPart("rUpperArm", -0.55f, 1.7f, -0.1f, 0.15f, 0.3f, 0.1f);
	this->rLowerArm = new BodyPart("rLowerArm", -0.55f, 1.4f, -0.1f, 0.15f, 0.4f, 0.1f);
	this->rHand = new BodyPart("rHand", -0.55f, 1.1f, -0.1f, 0.2f, 0.2f, 0.2f);
	
	this->rUpperArm->setTextureImg("color_rows.bmp");
	this->rUpperArm->setAmbientLightColor(0.0f, 1.0f, 0.0f, 1.0f);
	this->rUpperArm->setDiffuseLightColor(0.0f, 1.0f, 0.0f, 1.0f);
	this->rUpperArm->setSpecularLightColor(0.0f, 1.0f, 0.0f, 1.0f);
	
	this->rLowerArm->setTextureImg("color_rows.bmp");
	this->rLowerArm->setAmbientLightColor(0.0f, 1.0f, 0.0f, 1.0f);
	this->rLowerArm->setDiffuseLightColor(0.0f, 1.0f, 0.0f, 1.0f);
	this->rLowerArm->setSpecularLightColor(0.0f, 1.0f, 0.0f, 1.0f);
	
	this->rHand->setTextureImg("color_rows.bmp");
	this->rHand->setAmbientLightColor(0.0f, 1.0f, 0.0f, 1.0f);
	this->rHand->setDiffuseLightColor(0.0f, 1.0f, 0.0f, 1.0f);
	this->rHand->setSpecularLightColor(0.0f, 1.0f, 0.0f, 1.0f);
	
	this->lUpperArm = new BodyPart("lUpperArm", 0.55f, 1.7f, -0.1f, 0.15f, 0.3f, 0.1f);
	this->lLowerArm = new BodyPart("lLowerArm", 0.55f, 1.4f, -0.1f, 0.15f, 0.4f, 0.1f);
	this->lHand = new BodyPart("lHand", 0.55f, 1.1f, -0.1f, 0.2f, 0.2f, 0.2f);
	
	this->lUpperArm->setTextureImg("color_rows.bmp");
	this->lUpperArm->setAmbientLightColor(0.0f, 1.0f, 0.0f, 1.0f);
	this->lUpperArm->setDiffuseLightColor(0.0f, 1.0f, 0.0f, 1.0f);
	this->lUpperArm->setSpecularLightColor(0.0f, 1.0f, 0.0f, 1.0f);
	
	this->lLowerArm->setTextureImg("color_rows.bmp");
	this->lLowerArm->setAmbientLightColor(0.0f, 1.0f, 0.0f, 1.0f);
	this->lLowerArm->setDiffuseLightColor(0.0f, 1.0f, 0.0f, 1.0f);
	this->lLowerArm->setSpecularLightColor(0.0f, 1.0f, 0.0f, 1.0f);
	
	this->lHand->setTextureImg("color_rows.bmp");
	this->lHand->setAmbientLightColor(0.0f, 1.0f, 0.0f, 1.0f);
	this->lHand->setDiffuseLightColor(0.0f, 1.0f, 0.0f, 1.0f);
	this->lHand->setSpecularLightColor(0.0f, 1.0f, 0.0f, 1.0f);
	
	this->rUpperLeg = new BodyPart("rUpperLeg", -0.4f, 1.0f, -0.1f, 0.15f, 0.3f, 0.1f);
	this->rLowerLeg = new BodyPart("rLowerLeg", -0.4f, 0.7f, -0.1f, 0.15f, 0.3f, 0.1f);
	this->rFoot = new BodyPart("rFoot", -0.4f, 0.4f, 0.0f, 0.2f, 0.1f, 0.3f);
	
	this->rUpperLeg->setTextureImg("color_rows.bmp");
	this->rUpperLeg->setAmbientLightColor(0.0f, 0.0f, 1.0f, 1.0f);
	this->rUpperLeg->setDiffuseLightColor(0.0f, 0.0f, 1.0f, 1.0f);
	this->rUpperLeg->setSpecularLightColor(0.0f, 0.0f, 1.0f, 1.0f);
	
	this->rLowerLeg->setTextureImg("color_rows.bmp");
	this->rLowerLeg->setAmbientLightColor(0.0f, 0.0f, 1.0f, 1.0f);
	this->rLowerLeg->setDiffuseLightColor(0.0f, 0.0f, 1.0f, 1.0f);
	this->rLowerLeg->setSpecularLightColor(0.0f, 0.0f, 1.0f, 1.0f);
	
	this->rFoot->setTextureImg("color_rows.bmp");
	this->rFoot->setAmbientLightColor(0.0f, 0.0f, 1.0f, 1.0f);
	this->rFoot->setDiffuseLightColor(0.0f, 0.0f, 1.0f, 1.0f);
	this->rFoot->setSpecularLightColor(0.0f, 0.0f, 1.0f, 1.0f);
	
	this->lUpperLeg = new BodyPart("lUpperLeg", 0.4f, 1.0f, -0.1f, 0.15f, 0.3f, 0.1f);
	this->lLowerLeg = new BodyPart("lLowerLeg", 0.4f, 0.7f, -0.1f, 0.15f, 0.3f, 0.1f);
	this->lFoot = new BodyPart("lFoot", 0.4f, 0.4f, 0.0f, 0.2f, 0.1f, 0.3f);
	
	this->lUpperLeg->setTextureImg("color_rows.bmp");
	this->lUpperLeg->setAmbientLightColor(0.0f, 0.0f, 1.0f, 1.0f);
	this->lUpperLeg->setDiffuseLightColor(0.0f, 0.0f, 1.0f, 1.0f);
	this->lUpperLeg->setSpecularLightColor(0.0f, 0.0f, 1.0f, 1.0f);
	
	this->lLowerLeg->setTextureImg("color_rows.bmp");
	this->lLowerLeg->setAmbientLightColor(0.0f, 0.0f, 1.0f, 1.0f);
	this->lLowerLeg->setDiffuseLightColor(0.0f, 0.0f, 1.0f, 1.0f);
	this->lLowerLeg->setSpecularLightColor(0.0f, 0.0f, 1.0f, 1.0f);
	
	this->lFoot->setTextureImg("color_rows.bmp");
	this->lFoot->setAmbientLightColor(0.0f, 0.0f, 1.0f, 1.0f);
	this->lFoot->setDiffuseLightColor(0.0f, 0.0f, 1.0f, 1.0f);
	this->lFoot->setSpecularLightColor(0.0f, 0.0f, 1.0f, 1.0f);
}

void Robot::rotateLimb(float angle, float x, float y, float z){
	this->curLimb->rotate(angle, x, y, z);
}

void Robot::setEditableLimb(int limb){
	switch (limb) {
		case HEAD:
			this->curLimb = this->head;
			break;
		case UPPER_TORSO:
			this->curLimb = this->upperTorso;
			break;
		case LOWER_TORSO:
			this->curLimb = this->lowerTorso;
			break;
		case UPPER_LEFT_ARM:
			this->curLimb = this->lUpperArm;
			break;
		case LOWER_LEFT_ARM:
			this->curLimb = this->lLowerArm;
			break;
		case LEFT_HAND:
			this->curLimb = this->lHand;
			break;
		case UPPER_RIGHT_ARM:
			this->curLimb = this->rUpperArm;
			break;
		case LOWER_RIGHT_ARM:
			this->curLimb = this->rLowerArm;
			break;
		case RIGHT_HAND:
			this->curLimb = this->rHand;
			break;
		case UPPER_LEFT_LEG:
			this->curLimb = this->lUpperLeg;
			break;
		case LOWER_LEFT_LEG:
			this->curLimb = this->lLowerLeg;
			break;
		case LEFT_FOOT:
			this->curLimb = this->lFoot;
			break;
		case UPPER_RIGHT_LEG:
			this->curLimb = this->rUpperLeg;
			break;
		case LOWER_RIGHT_LEG:
			this->curLimb = this->rLowerLeg;
			break;
		case RIGHT_FOOT:
			this->curLimb = this->rFoot;
			break;
		default:
			break;
	}	
}

/**
 * Draw each of the robot's limbs
 */
void Robot::draw(){
	glPushMatrix();
		this->upperTorso->draw();
	
		glPushMatrix();
			this->head->draw();
		glPopMatrix();
		
		glPushMatrix();
			this->rUpperArm->draw();
			glPushMatrix();
				this->rLowerArm->draw();
				glPushMatrix();
					this->rHand->draw();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
		
		glPushMatrix();
			this->lUpperArm->draw();
			glPushMatrix();
				this->lLowerArm->draw();
				glPushMatrix();
					this->lHand->draw();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
	
	glPushMatrix();
		this->lowerTorso->draw();
		
		glPushMatrix();
			this->rUpperLeg->draw();
			glPushMatrix();
				this->rLowerLeg->draw();
				glPushMatrix();
					this->rFoot->draw();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	
		glPushMatrix();
			this->lUpperLeg->draw();
			glPushMatrix();
				this->lLowerLeg->draw();
				glPushMatrix();
					this->lFoot->draw();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

string Robot::toString(){
	string out = "";
	
	out += this->upperTorso->toString();
	
	out += this->head->toString();
	
	out += this->rUpperArm->toString();
	out += this->rLowerArm->toString();
	out += this->rHand->toString();
	
	out += this->lUpperArm->toString();
	out += this->lLowerArm->toString();
	out += this->lHand->toString();
	
	out += this->lowerTorso->toString();
	
	out += this->rUpperLeg->toString();
	out += this->rLowerLeg->toString();
	out += this->rFoot->toString();
	
	out += this->lUpperLeg->toString();
	out += this->lLowerLeg->toString();
	out += this->lFoot->toString();
	
	return out;
}