/*
 *  Robot.h
 *  Project 2
 *
 *  A class that will draw a robot in a window.
 *
 */

#include "BodyPart.h"

class Robot {
private:
	BodyPart *head;
	BodyPart *upperTorso, *lowerTorso;
	BodyPart *lUpperArm, *lLowerArm, *rUpperArm, *rLowerArm;
	BodyPart *lHand, *rHand;
	BodyPart *lUpperLeg, *lLowerLeg, *rUpperLeg, *rLowerLeg;
	BodyPart *lFoot, *rFoot;
	BodyPart *curLimb;
	
public:
	Robot();
	
	void rotateLimb(float angle, float x, float y, float z);
	void setEditableLimb(int limb);
	void draw();
};