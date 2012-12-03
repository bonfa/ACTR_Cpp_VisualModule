/*
 * Triangle.h
 *
 *  Created on: 30/ott/2012
 *      Author: enrico
 */

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "utils.h"
#include "Blob.h"
#include "FeatureGetterExceptions.h"
#include "StraightLine.h"
using namespace std;


class Triangle: public Blob {
public:
	Triangle(int ax,int ay,int bx,int by,int cx,int cy);
	virtual ~Triangle();
	string getChunk();
	Point getA();
	Point getB();
	Point getC();
private:
	Point a;
	Point b;
	Point c;
	void setBoundingBox();
};

#endif /* TRIANGLE_H_ */
