/*
 * Circle.cpp
 *
 *  Created on: 31/ott/2012
 *      Author: enrico
 */

#include "Circle.h"
#include <math.h>

Circle::~Circle() {
	// TODO Auto-generated destructor stub
}

Circle::Circle(int rad, int x, int y) {
	if(x < 0 || y < 0 || rad <= 0 || x-rad <0 || y-rad <0)
		throw InputException(("Negative values in the points coordinates"));
	radius = rad;
	xCenter = x;
	yCenter = y;
	area = rad * rad * M_PI;
	setBbox(x-rad, y-rad, 2*rad, 2*rad);
}

string Circle::getChunk(){
	return "cianc, Circle\n";
}
