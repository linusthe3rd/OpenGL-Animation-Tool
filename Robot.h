/*
 *  Robot.h
 *  Homework4
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
	
public:
	Robot();
	
	void draw();
};