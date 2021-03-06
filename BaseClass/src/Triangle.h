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
	Triangle(int ax,int ay,int bx,int by,int cx,int cy, string color);
	virtual ~Triangle();
	/** Returns a string which contains the basic information about the triangle*/
	string getChunk();
	/** Returns the first vertex of the triangle*/
	Point getA();
	/** Returns the second vertex of the triangle*/
	Point getB();
	/** Returns the third vertex of the triangle*/
	Point getC();
protected:
	/** Creates a Json object that contains the basic information about the quadrilateral*/
	virtual Json::Value getJson();
private:
	/** The first vertex*/
	Point a;
	/** The second vertex*/
	Point b;
	/** The third vertex*/
	Point c;
	/** Set the bounding box around the triangle.*/
	void setBoundingBox();
	/** Set the 'rotation' of the quadrilateral.
	 * The rotation is defined as the smallest angle of the segments in the counterclockwise direction starting from the horizontal direction on the right*/
	void setRotation();
	/** Return a vector containing the three segments of the triangle*/
	std::vector<Segment> getEdgesLine();
};

#endif /* TRIANGLE_H_ */
