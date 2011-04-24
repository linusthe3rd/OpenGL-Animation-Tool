/*
 *  Keyframe.h
 *  Homework4
 *
 *  Created by John Ryding on 4/21/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef _CHANNEL_H_
#define _CHANNEL_H_

#if defined(__APPLE__) || defined(MACOSX)
	#include <OpenGL/gl.h>	
	#include <GLUT/glut.h>
	#include <OpenGL/glu.h>
#else
	#include <GL/gl.h>
	#include <GL/glut.h>
	#include <GL/glu.h>
#endif

#include <vector>
#include <algorithm>
#include <string>
#include <math.h>

using namespace std;

#define FLAT_STR "flat"
#define LINEAR_STR "linear"
#define SMOOTH_STR "smooth"

#define Lerp(u, t0, t1) ( (1-u)*t0 ) + u*t1
#define InvLerp(t, t0, t1) ( t-t0 ) / (t1 - t0)

struct Keyframe {
	float Time; //The time in which the keyframe occurs
	float Value; //The value of the frame
	float TangentIn,TangentOut; //"flat", "linear", or "smooth"
	string RuleIn,RuleOut; 
	float A,B,C,D;
};

struct Keyframe_functor {
	bool operator()( const Keyframe &a, const Keyframe &b ){
		return a.Time < b.Time;
	}
};

struct Keyframe_Time_functor {
	bool operator()( float time, const Keyframe &frame){
		return time < frame.Time;
	}
};

const float HERMITE_MATRIX[16] = {
	2, -2, 1, 1,
	-3, 3, -2, -1,
	0, 0, 1, 0,
	1, 0, 0, 0
};


class Channel {
public:
	Channel();
	float Evaluate(float time);
	void insertKeyFrame(Keyframe *frame);
	void Precompute();
	float getMaxTime();
	
private:
	vector<struct Keyframe> keyFrameArr;
	void computeTangents();
	void computeConstants();
};

#endif