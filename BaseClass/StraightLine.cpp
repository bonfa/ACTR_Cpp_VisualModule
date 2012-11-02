/*
 * StraightLine.cpp
 *
 *  Created on: 02/nov/2012
 *      Author: francesco
 */

#include "StraightLine.h"

StraightLine::StraightLine(double a, double b, double c) {
	/**
	 * Set the equation of the straight line
	 * ay + bx + c = 0
	 * */
	this->a = a;
	this->b = b;
	this->c = c;
	this->slope = this->calculateSlope();
	this->intercept = this->calculateIntercept();
}

double StraightLine::calculateSlope(){
	if (this->a!=0)
		return -(this->b/this->a);
	else
		throw verticalLineException;
}


double StraightLine::calculateIntercept(){
	if (this->a!=0)
		return -(this->c/this->a);
	else
		throw verticalLineException;
}


bool StraightLine::isVertical(){
	if (this->a==0)
		return true;
	else
		return false;
}


StraightLine::~StraightLine() {
	// TODO Auto-generated destructor stub
}

