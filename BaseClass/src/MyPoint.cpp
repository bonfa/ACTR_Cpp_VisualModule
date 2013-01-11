/*
 * MyPoint.cpp
 *
 *  Created on: 13/nov/2012
 *      Author: francesco
 */

#include "MyPoint.h"

Point::Point(int x_,int y_) {
	x = x_;
	y = y_;
}


Point::Point() {
	x = 0;
	y = 0;
}

bool Point::operator==(const Point &other) const {
	return ((this->x == other.x) && (this->y == other.y));
}


Point::~Point() {
}

