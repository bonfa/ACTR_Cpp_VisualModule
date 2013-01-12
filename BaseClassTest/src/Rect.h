/*
 * Rect.h
 *
 *  Created on: 13/nov/2012
 *      Author: francesco
 *  This class represents a bounding box of rectangular shape.
 *  It is supposed to bound the objects detected.
 *
 *  It is defined by a point, which is the starting point of the rectangle
 *  and the width and the height of the rectangle itself.
 *  In a common 2D space, the point is the bottom-left point of the rectangle.
 *  In a 2D space as the one defined by the opencv Mat it is the top left point of the rectangle.
 *  @ATTENTION: the coordinates must not be negative
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
	virtual ~Rect();
	/** Return 4 the equations of the segment of the square */
	std::vector<Segment> getEdgesLine();
	/** Return 4 the points of the square */
	std::vector<Point> getPoints();
	/** Two rects are equal when the four parameter x,y,height and width are equal*/
	bool operator==(const Rect &other) const;
	/** The x point of the vertex of the rect*/
	int x;
	/** The y point of the vertex of the rect*/
	int y;
	/** The height of the rect*/
	int height;
	/** The width of the vertex of the rect*/
	int width;
};

#endif /* RECT_H_ */
