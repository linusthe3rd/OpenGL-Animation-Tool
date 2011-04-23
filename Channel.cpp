/*
 *  Keyframe.cpp
 *  Homework4
 *
 *  Created by John Ryding on 4/21/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Channel.h"

Channel::Channel() : keyFrameArr(){}

float Channel::Evaluate(float time){
	vector<Keyframe>::iterator ubIter = upper_bound(keyFrameArr.begin(), keyFrameArr.end(), time, cmpKeyframeTimes);
	Keyframe k1 = *ubIter;
	Keyframe k0 = *(--ubIter);
	
	float u = InvLerp(time, k0.Time, k1.Time);
	//float t = Lerp(u, k0->Time, k1->Time);
	
	//return ( k0->A * pow(t, 3) ) + ( k0->B * pow(t, 2) ) + ( k0->C * t ) + k0->D;
	return k0.D + u*( k0.C + u*( k0.B + u*k0.A) );
}

void Channel::insertKeyFrame(Keyframe frame){
	keyFrameArr.push_back(frame);
	sort(keyFrameArr.begin(), keyFrameArr.end(), cmpKeyframes);
	this->Precompute();
}

void Channel::Precompute(){
	this->computeTangents();
	this->computeConstants();
}

void Channel::computeTangents(){
	for (int i = 0; i < keyFrameArr.size(); i++) {
		if (i == 0) {
			keyFrameArr[i].TangentIn = 0;
			
			if (strcmp(&(keyFrameArr[i].RuleOut), LINEAR_STR) == 0) {
				keyFrameArr[i].TangentOut = (keyFrameArr[i+1].Value - keyFrameArr[i].Value) / ( keyFrameArr[i+1].Time - keyFrameArr[i].Time );
			} else {
				keyFrameArr[i].TangentOut = 0;
			}
		} else if (i == keyFrameArr.size()-1) {
			keyFrameArr[i].TangentOut = 0;
			
			if (strcmp(&(keyFrameArr[i].RuleIn), LINEAR_STR) == 0) {
				keyFrameArr[i].TangentIn = (keyFrameArr[i].Value - keyFrameArr[i-1].Value) / ( keyFrameArr[i].Time - keyFrameArr[i-1].Time );
			} else {
				keyFrameArr[i].TangentIn = 0;
			}
		} else {
			if (strcmp(&(keyFrameArr[i].RuleIn), FLAT_STR) == 0) {
				keyFrameArr[i].TangentIn = 0;
			} else if (strcmp(&(keyFrameArr[i].RuleIn), LINEAR_STR) == 0) {
				keyFrameArr[i].TangentIn = (keyFrameArr[i].Value - keyFrameArr[i-1].Value) / ( keyFrameArr[i].Time - keyFrameArr[i-1].Time );
			} else if (strcmp(&(keyFrameArr[i].RuleIn), SMOOTH_STR) == 0) {
				keyFrameArr[i].TangentIn = (keyFrameArr[i+1].Value - keyFrameArr[i-1].Value) / ( keyFrameArr[i+1].Time - keyFrameArr[i-1].Time );
			}
			
			if (strcmp(&(keyFrameArr[i].RuleOut), FLAT_STR) == 0) {
				keyFrameArr[i].TangentOut = 0;
			} else if (strcmp(&(keyFrameArr[i].RuleOut), LINEAR_STR) == 0) {
				keyFrameArr[i].TangentOut = (keyFrameArr[i+1].Value - keyFrameArr[i].Value) / ( keyFrameArr[i+1].Time - keyFrameArr[i].Time );
			} else if (strcmp(&(keyFrameArr[i].RuleOut), SMOOTH_STR) == 0) {
				keyFrameArr[i].TangentOut = (keyFrameArr[i+1].Value - keyFrameArr[i-1].Value) / ( keyFrameArr[i+1].Time - keyFrameArr[i-1].Time );
			}
		}
		
	}
}

void Channel::computeConstants(){
	glMatrixMode(GL_MODELVIEW);
	
	for (int i = 0; i < keyFrameArr.size(); i++) {
		if (i != keyFrameArr.size()-1) {
			float frameMatrix[16] = {
				keyFrameArr[i].Value, 0, 0, 0,
				keyFrameArr[i+1].Value, 0, 0, 0,
				keyFrameArr[i].TangentOut, 0, 0, 0,
				keyFrameArr[i+1].TangentIn, 0, 0, 0
			};
			
			glPushMatrix();
				glLoadIdentity();
				glMultMatrixf(HERMITE_MATRIX);
				glMultMatrixf(frameMatrix);
				glGetFloatv(GL_MODELVIEW_MATRIX, frameMatrix);
			glPopMatrix();
			
			keyFrameArr[i].A = frameMatrix[0];
			keyFrameArr[i].B = frameMatrix[4];
			keyFrameArr[i].C = frameMatrix[8];
			keyFrameArr[i].D = frameMatrix[12];
		}
	}
}