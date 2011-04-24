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

#include "Channel.h"
#include "Robot.h"

class Player{
public:
	Player(Robot* _rbt, int _framerate);
	
	void addKeyFrame();
	
	void play(bool isForward);
	void stop();
	
	void incrementFrame();
	void decrementFrame();
	
	void setFramerate(int rate);
	int getFramerate();
	
private:
	vector<Channel> channels;
	Robot *rbt;
	
	float currentTime;
	int framerate;
	float increment;
	
	void updatePose();
};

#endif