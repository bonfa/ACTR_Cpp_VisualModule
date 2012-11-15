/*
 * MyPoint.h
 *
 *  Created on: 13/nov/2012
 *      Author: francesco
 */

#ifndef MYPOINT_H_
#define MYPOINT_H_

#include "BaseClassException.h"

class Point {
public:
	Point(int x,int y);
	Point();
	virtual ~Point();
	bool operator==(const Point &other) const;
	int x;
	int y;
};

#endif /* MYPOINT_H_ */



