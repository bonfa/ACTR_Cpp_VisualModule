/*
 * Circle.h
 *
 *  Created on: 31/ott/2012
 *      Author: enrico
 *
 *  This class represent the circular geometric shape.
 *  It is defined by the coordinates of the center and the radius of the circle.
 *  @ATTENTION: the coordinates must not be negative
 */

#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "Blob.h"
#include "MyPoint.h"


class Circle: public Blob {
public:
	Circle(int rad, int x, int y, string color);
	/** Returns a string which contains the basic information about the circle*/
	string getChunk();
	/** Returns the x coordinate of the center*/
	int getXCenter();
	/** Returns the y coordinate of the center*/
	int getYCenter();
	/** Returns the radius of the circle*/
	int getRadius();
	/** Returns the center of the circle*/
	Point getCenter();
	virtual ~Circle();
protected:
	/** Creates a Json object that contains the basic information about the quadrilateral*/
	virtual Json::Value getJson();
private:
	/** The area of the circle*/
	double area;
	/** The center of the circle*/
	Point center;
	/** The radius of the circle*/
	int radius;
	/** Set the 'rotation' of the circle, which is always zero*/
	void setRotation();
};

#endif /* CIRCLE_H_ */
