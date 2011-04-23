/*
 *  Robot.h
 *  Project 2
 *
 *  A class that will draw a robot in a window.
 *
 */
#ifndef _ROBOT_H_
#define _ROBOT_H_

#include "BodyPart.h"
#include "Util.h"

#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Robot {
private:
	map<string, BodyPart*> limbMap;
	
	BodyPart *head;
	BodyPart *upperTorso, *lowerTorso;
	BodyPart *lUpperArm, *lLowerArm, *rUpperArm, *rLowerArm;
	BodyPart *lHand, *rHand;
	BodyPart *lUpperLeg, *lLowerLeg, *rUpperLeg, *rLowerLeg;
	BodyPart *lFoot, *rFoot;
	BodyPart *curLimb;
	
public:
	Robot();
	
	void loadPose(char* fName);
	vector<string> splitStringBySpace(string str);
	void rotateLimb(float angle, float x, float y, float z);
	void setEditableLimb(int limb);
	void draw();
	string toString();
};
#endif