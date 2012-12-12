/*
 * StraightLine.cpp
 *
 *  Created on: 02/nov/2012
 *      Author: francesco
 */

#include "StraightLine.h"

/**
 * 1) Set the equation of the straight line    ay + bx + c = 0
 * 2) Set the slope and the intercept of the straight line
 * */
StraightLine::StraightLine(double a, double b, double c) {
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


/**
 * 1) Check if the points are not the same point
 * 2) Set the equation of the straight line    ay + bx + c = 0
 * 3) Set the slope and the intercept of the straight line
 * */
StraightLine::StraightLine(int xa, int ya, int xb, int yb){
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


/**
 * 1) Check if the points are not the same point
 * 2) Set the equation of the straight line    ay + bx + c = 0
 * 3) Set the slope and the intercept of the straight line
 * */
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


/** @ATTENTION: If the line is vertical it raises an exception*/
double StraightLine::calculateSlope(){
	//TODO: change the control --> done
	// if (a != 0)
	if (! areSame(this->a,0))
		return -(this->b/this->a);
	else
		throw VerticalLineException();
}

/** @ATTENTION: If the line is vertical it raises an exception*/
double StraightLine::getSlope(){
	if (this->isVertical())
		throw VerticalLineException();
	else
		return this->slope;
}

/** @ATTENTION: If the line is vertical it raises an exception*/
double StraightLine::getIntercept(){
	if (this->isVertical())
		throw VerticalLineException();
	else
		return this->intercept;
}


/** @ATTENTION: If the line is vertical it raises an exception*/
double StraightLine::calculateIntercept(){
	//TODO: change the control
	//if (this->a!=0)
	if(!areSame(a,0))
		return -(this->c/this->a);
	else
		throw VerticalLineException();
}

/** @ATTENTION: If the line is vertical it raises an exception*/
bool StraightLine::isVertical(){
	//TODO: change the control
	//if (this->a==0)
	if(areSame(a,0))
		return true;
	else
		return false;
}

bool StraightLine::doesPointBelongTo(int xp,int yp){
	//TODO: change the control
	//if (this->a * yp + this->b * xp + this->c == 0)
	if (areSame(this->a * yp + this->b * xp + this->c,0))
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
	//the case in which both of the lines are vertical is handled above

	//one of the two lines is vertical
	if(this->isVertical())
		return (line2.getInterceptionPointWithVertical(*this));

	else if (line2.isVertical())
		return this->getInterceptionPointWithVertical(line2);

	//non of two lines is vertical
	double m1 = this->slope;
	double q1 = this->intercept;
	double m2 = line2.getSlope();
	double q2 = line2.getIntercept();
	double xp = (double(q2-q1))/(double(m1-m2));
	double yp = this->getY(xp);

	return Point(round(xp),round(yp));
}



Point StraightLine::getInterceptionPointWithVertical(StraightLine verticalLine){
	double xp = -verticalLine.getC()/verticalLine.getB();
	double yp = (-this->c - this->b*xp) / this->a;
	return Point(round(xp),round(yp));
}



bool StraightLine::isParallel(StraightLine line2){
	if (this->isVertical() && line2.isVertical())
			return true;

	else if (!this->isVertical() && !line2.isVertical()){
		return ((areSame(this->slope,line2.getSlope())));
	}

	else	//one vertical and one not
		return false;
}



bool StraightLine::isCoincident(StraightLine line2){
	if (this->isVertical() && line2.isVertical())
		return (areSame(this->intercept,line2.getIntercept()));

	else if (!this->isVertical() && !line2.isVertical()){
		return ((areSame(this->slope,line2.getSlope())) && (areSame(this->intercept,line2.getIntercept())));
	}

	else	//one vertical and one not
		return false;


}


/** @ATTENTION: the input and the output value are double (and not integer)*/
double StraightLine::getY(double xp){
	return (slope*xp+intercept);
}

