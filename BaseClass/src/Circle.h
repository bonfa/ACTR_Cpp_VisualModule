/*
 * Circle.h
 *
 *  Created on: 31/ott/2012
 *      Author: enrico
 */

#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "Blob.h"

class Circle: public Blob {
public:
	Circle(int rad, int x, int y);
	string getChunk();
	int getXCenter();
	int getYCenter();
	int getRadius();
	virtual ~Circle();
private:
	double area;
	int radius;
	int xCenter;
	int yCenter;
};

#endif /* CIRCLE_H_ */
