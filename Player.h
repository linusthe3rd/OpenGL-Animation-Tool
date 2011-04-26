/*
 *  Player.h
 *  Homework4
 *
 *  Created by John Ryding on 4/23/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Util.h"

#include "Channel.h"
#include "Robot.h"

class Player{
public:
	Player(Robot* _rbt);
	
	void addKeyFrame();
	
	void play();
	void stop();
	
	void incrementFrame(int *frameCnt);
	void decrementFrame(int *frameCnt);
	
	void setFramerate(int rate);
	int getFramerate();
	
	void setPlayDirection(bool direction);
	
	string toString();
	
	void loadAnim(char* fName);
	
private:
	vector<Channel> channels;
	Robot *rbt;
	
	int currentFrame;
	int keyframeAmt;
	bool isForward;
	
	bool updatePose(bool isForward);
};

#endif