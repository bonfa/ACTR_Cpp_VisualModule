/*
 * Circle.h
 *
 *  Created on: 31/ott/2012
 *      Author: enrico
 */

#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "Blob.h"
#include "MyPoint.h"


class Circle: public Blob {
public:
	Circle(int rad, int x, int y);
	string getChunk();
	int getXCenter();
	int getYCenter();
	int getRadius();
	Point getCenter();
	virtual ~Circle();
private:
	double area;
	Point center;
	int radius;
};

#endif /* CIRCLE_H_ */
