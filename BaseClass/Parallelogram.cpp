/*
 * Parallelogram.cpp
 *
 *  Created on: 30/ott/2012
 *      Author: enrico
 */

#include "Parallelogram.h"

Parallelogram::Parallelogram() {
	// TODO Auto-generated constructor stub

}

Parallelogram::~Parallelogram() {
	// TODO Auto-generated destructor stub
}

Parallelogram::Parallelogram(int ax,int ay,int bx,int by,int cx,int cy,int dx,int dy){
	a = cvPoint(ax, ay);
	b = cvPoint(bx, by);
	c = cvPoint(cx, cy);
	d = cvPoint(dx, dy);
}

string Parallelogram::getChunk(){
	return "cianc, parallelogram\n";
}

double Parallelogram::getArea(){
	return 2*(erone(a, b, c));
}
