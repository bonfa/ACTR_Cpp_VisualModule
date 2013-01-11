/*
 * MyPoint.h
 *
 *  Created on: 13/nov/2012
 *      Author: francesco
 *
 *  This class represents a 2D point.
 *  It is defined by its x and y coordinates.
 */

#ifndef MYPOINT_H_
#define MYPOINT_H_

#include "FeatureGetterExceptions.h"

class Point {
public:
	Point();
	Point(int x,int y);
	/** Two points are equal when the x and the y coordinates are equal*/
	bool operator==(const Point &other) const;
	virtual ~Point();

	/** The x coordinate of the point*/
	int x;
	/** The y coordinate of the pont*/
	int y;

};

#endif /* MYPOINT_H_ */



