/*
 *  Robot.h
 *  Homework4
 *
 *  Created by John Ryding on 4/4/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
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