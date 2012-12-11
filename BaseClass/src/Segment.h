/*
 * Segment.h
 *
 *  Created on: 11/dic/2012
 *      Author: francesco
 */

#ifndef SEGMENT_H_
#define SEGMENT_H_

#include "StraightLine.h"
#include "MyPoint.h"
#include <vector>

using namespace std;


class Segment: StraightLine {
public:
	Segment(Point a, Point b);
	Point getInterceptionPoint(Segment segment2);
	vector<Point> getPoints();
	bool isPointBetweenSegmentExtremes(Point p);
	virtual ~Segment();
private:
	int getMaxX();
	int getMinX();
	int getMaxY();
	int getMinY();
	Point p1;
	Point p2;
};

#endif /* SEGMENT_H_ */
