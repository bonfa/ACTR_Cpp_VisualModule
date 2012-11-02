/*
 * Circle.cpp
 *
 *  Created on: 31/ott/2012
 *      Author: enrico
 */

#include "Circle.h"
#include <math.h>

Circle::Circle(): area(0), radius(0), xCenter(0), yCenter(0){
	// TODO Auto-generated constructor stub

}

Circle::~Circle() {
	// TODO Auto-generated destructor stub
}

Circle::Circle(int rad, int x, int y): area(0), radius(rad), xCenter(x), yCenter(y){
	if(x<0 || y < 0 || radius <= 0 || x-rad <0 || y-rad <0)
		printf("Eccezione");
	area = rad * rad * M_PI;
	setBbox(x-rad, y-rad, 2*rad, 2*rad);
}

string Circle::getChunk(){
	return "cianc, Circle\n";
}
