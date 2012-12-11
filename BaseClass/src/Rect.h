/*
 * Rect.h
 *
 *  Created on: 13/nov/2012
 *      Author: francesco
 */

#ifndef RECT_H_
#define RECT_H_

#include "FeatureGetterExceptions.h"
#include "MyPoint.h"
#include "StraightLine.h"
#include "Segment.h"
#include <vector>

using namespace std;

class Rect {
public:
	Rect();
	Rect(int x, int y, int height, int width);
	Rect(Point p, int height, int width);
	std::vector<Segment> getEdgesLine();
	std::vector<Point> getPoints();
	virtual ~Rect();
	bool operator==(const Rect &other) const;
	int x;
	int y;
	int height;
	int width;
};

#endif /* RECT_H_ */
