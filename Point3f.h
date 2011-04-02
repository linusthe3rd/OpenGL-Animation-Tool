/*
 *  Point3f.h
 *  Homework4
 *
 *  Created by John Ryding on 4/2/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef _POINT3F_H_
#define _POINT3F_H_

#include <math.h>

struct Point3f {
	float x, y, z;
	
	Point3f(){
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
	
	Point3f(float newX, float newY, float newZ){
		x = newX;
		y = newY;
		z = newZ;
	}
};

#endif
