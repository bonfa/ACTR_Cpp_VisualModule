/*
 * StraightLine.h
 *
 *  Created on: 02/nov/2012
 *      Author: francesco
 */

#ifndef STRAIGHTLINE_H_
#define STRAIGHTLINE_H_

#include "BaseClassException.h"

class StraightLine {
public:
	//StraightLine();
	StraightLine(double a, double b, double c);
	StraightLine(int xa, int ya, int xb, int yb);
	double getA();
	double getB();
	double getC();
	double getSlope();
	double getIntercept();
	bool isVertical();
	bool doesPointBelongTo(int xp,int yp);
	virtual ~StraightLine();
private:
	double calculateSlope();
	double calculateIntercept();
	double a;
	double b;
	double c;
	double slope;
	double intercept;
};


#endif /* STRAIGHTLINE_H_ */
