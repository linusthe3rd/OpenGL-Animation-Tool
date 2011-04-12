/*
 *  Vectors.h
 *  Project 2
 *
 *  A util class that defines vector formulas
 *
 */
#ifndef VECTORSUTIL_H
#define VECTORSUTIL_H

#include <math.h>

/**
 * Get the magnitude for a given vector
 */
#define magnitude(v) sqrt( pow(v[0], 2) + pow(v[1], 2) + pow(v[2], 2))

/**
 * Find the dot product of two vectors
 */
#define dotProduct(v,q) ((v)[0] * (q)[0] + (v)[1] * (q)[1] + (v)[2] * (q)[2])

#endif