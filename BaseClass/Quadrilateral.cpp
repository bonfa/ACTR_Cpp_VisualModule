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
		printf("Eccezione");//TODO
	if((ax == bx && bx == cx) || (ax == bx && bx == dx) ||(bx == cx && cx == dx) || (ax == cx && cx == dx) ||
			(ay == by && by == cy) || (ay == by && by == dy) ||(by == cy && cy == dy) || (ay == cy && cy == dy))
		printf("Eccezione");//TODO

	int maxX, minX, maxY, minY;

	a = cvPoint(ax, ay);
	b = cvPoint(bx, by);
	c = cvPoint(cx, cy);
	d = cvPoint(dx, dy);

	std::vector<CvPoint> coords;
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



string Quadrilateral::getChunk(){
	return "cianc, Quadrilateral\n";
}

