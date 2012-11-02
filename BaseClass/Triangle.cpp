/*
 * Triangle.cpp
 *
 *  Created on: 30/ott/2012
 *      Author: enrico
 */

#include "Triangle.h"

Triangle::Triangle() {
	// TODO Auto-generated constructor stub

}

Triangle::~Triangle() {
	// TODO Auto-generated destructor stub
}

Triangle::Triangle(int ax,int ay,int bx,int by,int cx,int cy,int dx,int dy){
	if(ax<0 || ay<0 || bx<0 || by<0 || cx<0 || cy<0)
		throw inputException("Negative values in the points coordinates");

	if((ax == bx && bx == cx) || (ay == by && by == cy))
		throw inputException("More thantwo points on the same line");
	//@TODO: gestire il caso in cui i punti siano su una stessa linea non orizzontale o verticale

	int maxX, minX, maxY, minY;

	a = cvPoint(ax, ay);
	b = cvPoint(bx, by);
	c = cvPoint(cx, cy);
	area = erone(a, b, c);

	std::vector<CvPoint> coords;
	coords.push_back(a);
	coords.push_back(b);
	coords.push_back(c);

	maxX = getMinMax(coords, MAX_X);
	maxY = getMinMax(coords, MAX_Y);
	minX = getMinMax(coords, MIN_X);
	minY = getMinMax(coords, MIN_Y);

	setBbox(minX, minY, maxY - minY, maxX-minX);
}

string Triangle::getChunk(){
	return "cianc, traingle\n";
}
