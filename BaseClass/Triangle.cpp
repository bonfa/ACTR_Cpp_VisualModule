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
	a = cvPoint(ax, ay);
	b = cvPoint(bx, by);
	c = cvPoint(cx, cy);
}

string Triangle::getChunk(){
	return "cianc, traingle\n";
}

double Triangle::getArea(){
	return (erone(a, b, c));
}
