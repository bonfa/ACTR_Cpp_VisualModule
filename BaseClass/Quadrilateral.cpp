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
	// TODO Auto-generated destructor stub
}

Quadrilateral::Quadrilateral(int ax,int ay,int bx,int by,int cx,int cy,int dx,int dy){
	a = cvPoint(ax, ay);
	b = cvPoint(bx, by);
	c = cvPoint(cx, cy);
	d = cvPoint(dx, dy);
}

string Quadrilateral::getChunk(){
	return "cianc, Quadrilateral\n";
}

double Quadrilateral::getArea(){
	return 2*(erone(a, b, c));
}
