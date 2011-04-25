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
	this->isForward = true;
}

void Player::addKeyFrame(){
	vector<float> limbRoation;
	int currentLimb = 0;
	
	for (int i = 0; i < channels.size(); i+=3) {
		limbRoation = this->rbt->getLimbRotation(currentLimb);
		
		Keyframe *frameX = new Keyframe();
		frameX->Time = float (this->keyframeAmt);
		frameX->Value = limbRoation[0];
		frameX->RuleIn = "flat";
		frameX->RuleOut = "flat";
		this->channels[i].insertKeyFrame(frameX);
		
		Keyframe *frameY = new Keyframe();
		frameY->Time = float (this->keyframeAmt);
		frameY->Value = limbRoation[1];
		frameY->RuleIn = "flat";
		frameY->RuleOut = "flat";
		this->channels[i+1].insertKeyFrame(frameY);
		
		Keyframe *frameZ = new Keyframe();
		frameZ->Time = float (this->keyframeAmt);
		frameZ->Value = limbRoation[2];
		frameZ->RuleIn = "flat";
		frameZ->RuleOut = "flat";
		this->channels[i+2].insertKeyFrame(frameZ);
		
		currentLimb++;
	}
	
	this->keyframeAmt++;
}

void Player::play(){
	while (this->currentTime < this->channels[0].getMaxTime()) {
		this->updatePose(this->isForward);
		this->currentTime += this->increment;	
		this->rbt->draw();
	}
}

void Player::stop(){}

void Player::incrementFrame(){
	this->currentTime += this->increment;
	this->updatePose(true);
}
void Player::decrementFrame(){
	this->currentTime -= this->increment;
	this->updatePose(false);
}

void Player::updatePose(bool isForward){
	float x=0.0, y=0.0, z=0.0;
	float direction = 1.0;
	
	if (!isForward) {
		direction = -1.0;
	}
	int curLimbIndex = 0;
	
	for (int i = 0; i < channels.size(); i+=3) {
		this->rbt->setEditableLimb(curLimbIndex);
		
		x = channels[i].Evaluate(this->currentTime) * direction;
		this->rbt->rotateLimb(x, 1.0, 0.0, 0.0);
		
		y = channels[i+1].Evaluate(this->currentTime) * direction;
		this->rbt->rotateLimb(y, 0.0, 1.0, 0.0);
		
		z = channels[i+2].Evaluate(this->currentTime) * direction;
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

void Player::setPlayDirection(bool direction){
	this->isForward = direction;
}