/*
 * Circle.cpp
 *
 *  Created on: 31/ott/2012
 *      Author: enrico
 */

#include "Circle.h"
#include <math.h>


/**
 * Constructor
 * 1) check that all the coordinates are not negative
 * 2) create the circle
 * 3) set the area
 * 4) set the bounding box
 * 5) the center of the bounding box is the center of the circle
 * */
Circle::Circle(int rad, int x, int y) {
	//TODO mettere a posto questo controllo!!!!
	if(x < 0 || y < 0 || rad <= 0 || x-rad <0 || y-rad <0)
		throw InputException(("Negative values in the points coordinates"));
	radius = rad;
	center.x = x;
	center.y = y;
	area = rad * rad * M_PI;
	setBbox(x-rad, y-rad, 2*rad, 2*rad);
	this->setRotation();
}

string Circle::getChunk(){ //TODO copy from quadrilateral
	return "cianc, Circle\n";
}


int Circle::getXCenter(){
	return this->center.x;
}


int Circle::getYCenter(){
	return this->center.y ;
}

Point Circle::getCenter(){
	return this->center;
}

int Circle::getRadius(){
	return this->radius;
}

void Circle::setRotation(){
	//A circle does not have a rotation parameter
	rotation = 0;
}

Circle::~Circle() {

}
