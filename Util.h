/*
 *  Util.h
 *  Homework4
 *
 *  Created by John Ryding on 4/14/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef _UTIL_H_
#define _UTIL_H_

#include <vector>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

vector<string> splitStringBySpace(string str);
double convertToFloat(string const& s);
int convertToInt(string const& s);

#endif