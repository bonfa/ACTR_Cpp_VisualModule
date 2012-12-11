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
	try {
		this->slope = this->calculateSlope();
		this->intercept = this->calculateIntercept();
	}
	catch(VerticalLineException & e){
		this->slope = NULL;
		this->intercept = NULL;
	}
}

StraightLine::StraightLine(int xa, int ya, int xb, int yb){
	/**
	 * Set the equation of the straight line
	 * ay + bx + c = 0
	 * */
	if (xa==xb && ya==yb)
		throw InputException("Coincident Points");
	else if (xa==xb && ya!=yb){
		this->a = 0;
		this->b = 1;
		this->c = -xa;
		this->slope = NULL;
		this->intercept = NULL;
	}
	else {
		this->a = xb-xa;
		this->b = -(yb-ya);
		this->c = (yb-ya)*xa - ya*(xb-xa);
		this->slope = double(yb-ya)/double(xb-xa);
		this->intercept = this->calculateIntercept();
	}
}


StraightLine::StraightLine(Point a, Point b){
	/**
	 * Set the equation of the straight line
	 * ay + bx + c = 0
	 * */
	if (a.x==b.x && a.y==b.y)
		throw InputException("Coincident Points");
	else if (a.x==b.x && a.y!=b.y){
		this->a = 0;
		this->b = 1;
		this->c = -a.x;
		this->slope = NULL;
		this->intercept = NULL;
	}
	else {
		this->a = b.x-a.x;
		this->b = -(b.y-a.y);
		this->c = (b.y-a.y)*a.x - a.y*(b.x-a.x);
		this->slope = double(b.y-a.y)/double(b.x-a.x);
		this->intercept = this->calculateIntercept();
	}
}


double StraightLine::calculateSlope(){
	if (this->a!=0)
		return -(this->b/this->a);
	else
		throw VerticalLineException();
}

double StraightLine::getSlope(){
	if (this->isVertical())
		throw VerticalLineException();
	else
		return this->slope;
}

double StraightLine::getIntercept(){
	if (this->isVertical())
		throw VerticalLineException();
	else
		return this->intercept;
}

double StraightLine::calculateIntercept(){
	if (this->a!=0)
		return -(this->c/this->a);
	else
		throw VerticalLineException();
}


bool StraightLine::isVertical(){
	if (this->a==0)
		return true;
	else
		return false;
}

bool StraightLine::doesPointBelongTo(int xp,int yp){
	if (this->a * yp + this->b * xp + this->c == 0)
			return true;
	else
			return false;
}

double StraightLine::getA(){
	return this->a;
}


double StraightLine::getB(){
	return this->b;
}


double StraightLine::getC(){
	return this->c;
}

StraightLine::~StraightLine() {
	// TODO Auto-generated destructor stub
}


Point StraightLine::getInterceptionPoint(StraightLine line2){
	if (this->isCoincident(line2))
		throw CoincidentLinesException();
	if (this->isParallel(line2))
		throw ParallelLinesException();

	//@todo: sistemare se la retta è verticale
	//else
	double m1 = this->slope;
	double q1 = this->intercept;
	double m2 = line2.getSlope();
	double q2 = line2.getIntercept();
	double xp = (double(q2-q1))/(double(m1-m2));
	double yp = this->getY(xp);

	return Point(int(xp),int(yp));
}


bool StraightLine::isParallel(StraightLine line2){
	//todo: controllare per rette verticali --> pendenza zero
	double slope2 = line2.getSlope();
	return (this->slope == slope2);
}



bool StraightLine::isCoincident(StraightLine line2){
	//todo: controllare per rette verticali
	double slope2 = line2.getSlope();
	double intercep2 = line2.getIntercept();
	return ((int(this->slope) == int(slope2)) && (int(this->intercept) == (intercep2)));
}



double StraightLine::getY(double xp){
	return (slope*xp+intercept);
}

