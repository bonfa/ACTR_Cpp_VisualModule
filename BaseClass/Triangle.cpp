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
			printf("Eccezione");//TODO
	if((ax == bx && bx == cx) || (ay == by && by == cy))
		printf("Eccezione");//TODO

	a = cvPoint(ax, ay);
	b = cvPoint(bx, by);
	c = cvPoint(cx, cy);
	area = erone(a, b, c);
}

string Triangle::getChunk(){
	return "cianc, traingle\n";
}
