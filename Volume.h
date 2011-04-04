/*
 *  Volume.h
 *  Homework4
 *
 *  Created by John Ryding on 4/3/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
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
