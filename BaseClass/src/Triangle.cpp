/*
 * Triangle.cpp
 *
 *  Created on: 30/ott/2012
 *      Author: enrico
 */

#include "Triangle.h"


Triangle::Triangle(int ax,int ay,int bx,int by,int cx,int cy){
	if(ax<0 || ay<0 || bx<0 || by<0 || cx<0 || cy<0)
		throw InputException(("Negative values in the points coordinates"));

	if((ax == bx && bx == cx) || (ay == by && by == cy))
		throw InputException("More than two points on the same line");

	if (inLinePoints(ax,ay,bx,by,cx,cy))
		throw InputException("More than two points on the same line");

	this->a = Point(ax, ay);
	this->b = Point(bx, by);
	this->c = Point(cx, cy);
	this->area = erone(this->a, this->b, this->c);
	this->setBoundingBox();
	this->setCenter();
}


void Triangle::setBoundingBox() {
	int maxX, minX, maxY, minY;
	std::vector<Point> coords;
	coords.push_back(a);
	coords.push_back(b);
	coords.push_back(c);
	maxX = getMinMax(coords, MAX_X);
	maxY = getMinMax(coords, MAX_Y);
	minX = getMinMax(coords, MIN_X);
	minY = getMinMax(coords, MIN_Y);
	setBbox(minX, minY, maxY - minY, maxX - minX);
}


string Triangle::getChunk(){
	return "cianc, traingle\n";
}


Point Triangle::getA(){
	return this->a;
}



Point Triangle::getB(){
	return this->b;
}



Point Triangle::getC(){
	return this->c;
}



Triangle::~Triangle() {
	// TODO Auto-generated destructor stub
}
