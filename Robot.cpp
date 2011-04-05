/*
 *  Robot.cpp
 *  Homework4
 *
 *  Created by John Ryding on 4/4/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Robot.h"

//BodyPart *lUpperArm, *lLowerArm, *rUpperArm, *rLowerArm;
//BodyPart *lHand, *rHand;
//BodyPart *lUpperLeg, *lLowerLeg, *rUpperLeg, *rLowerLeg;
//BodyPart *lFoor, *rFoot;

Robot::Robot(){
	this->head = new BodyPart(0.0f, 2.5f, 0.0f, 0.5f, 0.5f, 0.5f);
	this->head->setTextureImg("Baboon.bmp");
	
	this->upperTorso = new BodyPart(0.0f, 2.0f, 0.0f, 1.0f, 0.5f, 1.0f);
	this->lowerTorso = new BodyPart(0.0f, 1.5f, 0.0f, 1.0f, 0.5f, 1.0f);
	
	this->upperTorso->setTextureImg("color_rows.bmp");
	this->upperTorso->setAmbientLightColor(1.0f, 0.0f, 0.0f, 1.0f);
	this->upperTorso->setDiffuseLightColor(1.0f, 0.0f, 0.0f, 1.0f);
	this->upperTorso->setSpecularLightColor(1.0f, 0.0f, 0.0f, 1.0f);
	
	this->lowerTorso->setTextureImg("color_rows.bmp");
	this->lowerTorso->setAmbientLightColor(1.0f, 0.0f, 0.0f, 1.0f);
	this->lowerTorso->setDiffuseLightColor(1.0f, 0.0f, 0.0f, 1.0f);
	this->lowerTorso->setSpecularLightColor(1.0f, 0.0f, 0.0f, 1.0f);
	
	this->rUpperArm = new BodyPart(-0.55f, 1.7f, -0.1f, 0.15f, 0.3f, 0.1f);
	this->rLowerArm = new BodyPart(-0.55f, 1.4f, -0.1f, 0.15f, 0.4f, 0.1f);
	this->rHand = new BodyPart(-0.55f, 1.1f, -0.1f, 0.2f, 0.2f, 0.2f);
	
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
	
	this->lUpperArm = new BodyPart(0.55f, 1.7f, -0.1f, 0.15f, 0.3f, 0.1f);
	this->lLowerArm = new BodyPart(0.55f, 1.4f, -0.1f, 0.15f, 0.4f, 0.1f);
	this->lHand = new BodyPart(0.55f, 1.1f, -0.1f, 0.2f, 0.2f, 0.2f);
	
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
	
	this->rUpperLeg = new BodyPart(-0.4f, 1.0f, -0.1f, 0.15f, 0.3f, 0.1f);
	this->rLowerLeg = new BodyPart(-0.4f, 0.7f, -0.1f, 0.15f, 0.3f, 0.1f);
	this->rFoot = new BodyPart(-0.4f, 0.4f, 0.0f, 0.2f, 0.1f, 0.3f);
	
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
	
	this->lUpperLeg = new BodyPart(0.4f, 1.0f, -0.1f, 0.15f, 0.3f, 0.1f);
	this->lLowerLeg = new BodyPart(0.4f, 0.7f, -0.1f, 0.15f, 0.3f, 0.1f);
	this->lFoot = new BodyPart(0.4f, 0.4f, 0.0f, 0.2f, 0.1f, 0.3f);
	
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

void Robot::draw(){
	this->head->draw();
	
	this->upperTorso->draw();
	this->lowerTorso->draw();
	
	this->rUpperArm->draw();
	this->rLowerArm->draw();
	this->rHand->draw();
	
	this->lUpperArm->draw();
	this->lLowerArm->draw();
	this->lHand->draw();
	
	this->rUpperLeg->draw();
	this->rLowerLeg->draw();
	this->rFoot->draw();
	
	this->lUpperLeg->draw();
	this->lLowerLeg->draw();
	this->lFoot->draw();

}