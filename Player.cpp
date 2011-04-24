/*
 *  Player.cpp
 *  Homework4
 *
 *  Created by John Ryding on 4/23/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Player.h"

Player::Player(Robot* _rbt, int _framerate): channels(45) {
	this->rbt = _rbt;
	this->framerate = _framerate;
	this->increment = 1.0 / _framerate;
	this->currentTime = 0.0;
	this->keyframeAmt = 0;
}

void Player::addKeyFrame(){
	vector<float> limbRoation;
	int currentLimb = 0;
	
	for (int i = 0; i < channels.size(); i+=3) {
		limbRoation = this->rbt->getLimbRotation(currentLimb);
		
		Keyframe *frameX = new Keyframe();
		frameX->Time = this->keyframeAmt;
		frameX->Value = limbRoation[0];
		frameX->RuleIn = "flat";
		frameX->RuleOut = "flat";
		this->channels[i].insertKeyFrame(frameX);
		
		Keyframe *frameY = new Keyframe();
		frameY->Time = this->keyframeAmt;
		frameY->Value = limbRoation[1];
		frameY->RuleIn = "flat";
		frameY->RuleOut = "flat";
		this->channels[i+1].insertKeyFrame(frameY);
		
		Keyframe *frameZ = new Keyframe();
		frameZ->Time = this->keyframeAmt;
		frameZ->Value = limbRoation[2];
		frameZ->RuleIn = "flat";
		frameZ->RuleOut = "flat";
		this->channels[i+2].insertKeyFrame(frameZ);
		
		currentLimb++;
	}
	
	this->keyframeAmt++;
}

void Player::play(bool isForward){
	while (this->currentTime < this->channels[0].getMaxTime()) {
		this->updatePose();
		this->currentTime += this->increment;		
	}
}

void Player::stop(){}

void Player::incrementFrame(){
	this->currentTime += this->increment;
	this->updatePose();
}
void Player::decrementFrame(){
	this->currentTime -= this->increment;
	this->updatePose();
}

void Player::updatePose(){
	float x=0.0, y=0.0, z=0.0;
	int curLimbIndex = 0;
	
	for (int i = 0; i < channels.size(); i+=3) {
		this->rbt->setEditableLimb(curLimbIndex);
		
		x = channels[i].Evaluate(this->currentTime);
		this->rbt->rotateLimb(x, 1.0, 0.0, 0.0);
		
		y = channels[i].Evaluate(this->currentTime);
		this->rbt->rotateLimb(y, 0.0, 1.0, 0.0);
		
		z = channels[i].Evaluate(this->currentTime);
		this->rbt->rotateLimb(z, 0.0, 0.0, 1.0);
		
		curLimbIndex++;
	}
}

void Player::setFramerate(int rate){
	this->framerate = rate;
	this->increment = 1.0 / rate;
}

int Player::getFramerate(){
	return this->framerate;
}