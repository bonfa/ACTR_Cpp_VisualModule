/*
 * Segment.h
 *
 *  Created on: 11/dic/2012
 *      Author: francesco
 *
 * 	This class represent a geometric segment.
 * 	It inherits from StraightLine.
 * 	In addition, it has the extreme vertices of the segment.
 */

#ifndef SEGMENT_H_
#define SEGMENT_H_

#include "StraightLine.h"
#include "MyPoint.h"
#include <vector>

using namespace std;

//TODO: documentation
class Segment: StraightLine {
public:
	Segment(Point a, Point b);

	/** Returns the point (with integer coordinates) which is the result of the intersection of the segment and the input segment*/
	Point getInterceptionPoint(Segment segment2);

	/** Return a list containing the two points of the segment (a and b)*/
	vector<Point> getPoints();

	/** Return true if the input point is inside the square defined by the two points whose the segment is the diagonal*/
	bool isPointBetweenSegmentExtremes(Point p);
	virtual ~Segment();
private:
	/** Return the max between the x of a and the x of b*/
	int getMaxX();
	/** Return the min between the x of a and the x of b*/
	int getMinX();
	/** Return the max between the y of a and the y of b*/
	int getMaxY();
	/** Return the min between the y of a and the y of b*/
	int getMinY();
	/** The first vertix of the segment*/
	Point p1;
	/** The second vertix of the segment*/
	Point p2;
};

#endif /* SEGMENT_H_ */
