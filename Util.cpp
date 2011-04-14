/*
 *  Util.cpp
 *  Homework4
 *
 *  Created by John Ryding on 4/14/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Util.h"

vector<string> splitStringBySpace(string str){
	string buf;
    stringstream stream(str);
	
    vector<string> tokens;	
    while (stream >> buf)
        tokens.push_back(buf);
	
	return tokens;
}

double convertToFloat(std::string const& s)
{
	istringstream i(s);
	float x;
	if (!(i >> x))
		cout << "convertToFloat(\"" + s + "\")" << endl;
	return x;
}
