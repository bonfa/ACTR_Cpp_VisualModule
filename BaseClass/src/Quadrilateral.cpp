/*
 * Quadrilateral.cpp
 *
 *  Created on: 30/ott/2012
 *      Author: enrico
 */

#include "Quadrilateral.h"


Quadrilateral::Quadrilateral() {
	// TODO Auto-generated constructor stub
}

Quadrilateral::~Quadrilateral() {
}


Quadrilateral::Quadrilateral(int ax,int ay,int bx,int by,int cx,int cy,int dx,int dy){
	if(ax<0 || ay<0 || bx<0 || by<0 || cx<0 || cy<0 || dx<0 || dy<0)
		throw InputException("Negative coordinate");
	/*if((ax == bx && bx == cx) || (ax == bx && bx == dx) ||(bx == cx && cx == dx) || (ax == cx && cx == dx) ||
			(ay == by && by == cy) || (ay == by && by == dy) ||(by == cy && cy == dy) || (ay == cy && cy == dy))
		printf("Eccezione");//TODO*/

	if (inLinePoints(ax,ay,bx,by,cx,cy) || inLinePoints(ax,ay,bx,by,dx,dy) || inLinePoints(dx,dy,bx,by,cx,cy) ||inLinePoints(ax,ay,cx,cy,dx,dy))
		throw InputException("More than two points on the same line");

	int maxX, minX, maxY, minY;

	a = Point(ax, ay);
	b = Point(bx, by);
	c = Point(cx, cy);
	d = Point(dx, dy);

	std::vector<Point> coords;
	coords.push_back(a);
	coords.push_back(b);
	coords.push_back(c);
	coords.push_back(d);

	Sort4PointsClockwise(coords);

	a = coords.at(0);
	b = coords.at(1);
	c = coords.at(2);
	d = coords.at(3);

	area = erone(a, b, c) + erone(a, c , d);

	maxX = getMinMax(coords, MAX_X);
	maxY = getMinMax(coords, MAX_Y);
	minX = getMinMax(coords, MIN_X);
	minY = getMinMax(coords, MIN_Y);

	setBbox(minX, minY, maxY - minY, maxX-minX);
}


Point Quadrilateral::getA(){
	return this->a;
}



Point Quadrilateral::getB(){
	return this->b;
}



Point Quadrilateral::getC(){
	return this->c;
}


Point Quadrilateral::getD(){
	return this->d;
}



string Quadrilateral::getChunk(){
	return "cianc, Quadrilateral\n";
}

