/*
 *  Vectors.h
 *  Homework4
 *
 *  Created by John Ryding on 4/3/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef VECTORSUTIL_H
#define VECTORSUTIL_H

#include <math.h>

#define magnitude(v) sqrt( pow(v[0], 2) + pow(v[1], 2) + pow(v[2], 2))

#define dotProduct(v,q) ((v)[0] * (q)[0] + (v)[1] * (q)[1] + (v)[2] * (q)[2])

#endif