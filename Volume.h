/*
 *  Volume.h
 *  Project 2
 *
 *  A struct representing a volume (width, depth, height).
 *
 */
#ifndef _VOLUME_H_
#define _VOLUME_H_

#include <math.h>

struct Volume {
	float w, h, d;
	
	Volume(){
		w = 0.0f;
		h = 0.0f;
		d = 0.0f;
	}
	
	Volume(float width, float height, float depth){
		w = width;
		h = height;
		d = depth;
	}
};

#endif
