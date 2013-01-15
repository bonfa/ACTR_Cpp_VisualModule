/*
 * StraightLine.h
 *
 *  Created on: 02/nov/2012
 *      Author: francesco
 *
 *  This class represent the straight line geometric shape.
 *  It is defined by:
 *  	the three coordinates a,b,c of the equation   a*y + b*x + c = 0
 *  	slope (m) and intercept (q) of the equation   y = m*x + q
 *
 */

#ifndef STRAIGHTLINE_H_
#define STRAIGHTLINE_H_

#include "FeatureGetterExceptions.h"
#include "MyPoint.h"
#include "utils.h"

class StraightLine {
public:
	/** Construct the line starting from the values a,b,c*/
	StraightLine(double a, double b, double c);

	/** Construct the line starting from the coordinates of two ponts*/
	StraightLine(int xa, int ya, int xb, int yb);

	/** Construct the line starting from two ponts*/
	StraightLine(Point a, Point b);

	double getA();
	double getB();
	double getC();
	double getSlope();
	double getIntercept();

	/** Returns true if the line is vertical*/
	bool isVertical();

	/** Returns true if the input point belongs to the line*/
	bool doesPointBelongTo(int xp,int yp);

	/** Returns true if the line and the input line are parallel*/
	bool isParallel(StraightLine line2);

	/** Returns true if the line and the input line are the same line*/
	bool isCoincident(StraightLine line2);

	/** Returns the point (with integer coordinates) which is the result of the intersection of the line and the input line*/
	Point getInterceptionPoint(StraightLine line2);

	/** Returns the point which is the result of the intersection of the line and the input line,
	 *  and the second line must be vertical*/
	Point getInterceptionPointWithVertical(StraightLine verticalLine);

	/** Given in input the x of a point on the lines, the method returns the y of that point*/
	double getY(double xp);

	virtual ~StraightLine();

private:
	/** Calculates the slope of the straight line from the parameters a,b,c*/
	double calculateSlope();

	/** Calculates the intercept of the straight line from the parameters a,b,c*/
	double calculateIntercept();

	/**the a coordinate of the equation   a*y + b*x + c = 0*/
	double a;

	/**the b coordinate of the equation   a*y + b*x + c = 0*/
	double b;

	/**the c coordinate of the equation   a*y + b*x + c = 0*/
	double c;

	/**the m of the equation   y = m*x + q */
	double slope;

	/**the q of the equation   y = m*x + q */
	double intercept;
};


#endif /* STRAIGHTLINE_H_ */
