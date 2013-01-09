/*
 * Triangle.h
 *
 *  Created on: 30/ott/2012
 *      Author: enrico
 *
 *  This class represent the triangular geometric shape.
 *  It is defined by its three vertices.
 *  @ATTENTION: the coordinates must not be negative
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
	/** Returns a string which contains the basic information about the triangle*/
	string getChunk();
	/** Returns the first vertex of the triangle*/
	Point getA();
	/** Returns the second vertex of the triangle*/
	Point getB();
	/** Returns the third vertex of the triangle*/
	Point getC();
private:
	/** The first vertex*/
	Point a;
	/** The second vertex*/
	Point b;
	/** The third vertex*/
	Point c;
	/** Set the bounding box around the triangle.*/
	void setBoundingBox();

	void setRotation();
};

#endif /* TRIANGLE_H_ */
