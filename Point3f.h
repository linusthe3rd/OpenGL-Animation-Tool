/*
 *  Point3f.h
 *  Project 2
 *
 *  A struct representing a 3D point.
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
