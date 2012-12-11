/*
 * Segment.cpp
 *
 *  Created on: 11/dic/2012
 *      Author: francesco
 */

#include "Segment.h"

Segment::Segment(Point a, Point b): StraightLine(a,b){
	this->p1 = a;
	this->p2 = b;
}

Segment::~Segment() {
	// TODO Auto-generated destructor stub
}



vector<Point> Segment::getPoints(){
	vector<Point> pointList;
	pointList.push_back(p1);
	pointList.push_back(p2);
	return pointList;
}


Point Segment::getInterceptionPoint(Segment segment2){
	Point interception;
	try {
		interception = StraightLine::getInterceptionPoint(segment2);
		if (this->isPointBetweenSegmentExtremes(interception) && segment2.isPointBetweenSegmentExtremes(interception))
			return interception;
		else
			throw NotOverlappedSegmentException();
	}
	catch (ParallelLinesException &e){
		throw NotOverlappedSegmentException();
	}
}



bool Segment::isPointBetweenSegmentExtremes(Point p){
	//if (StraightLine::doesPointBelongTo(p.x,p.y)){
		int maxX = getMaxX();
		int minX = getMinX();
		int maxY = getMaxY();
		int minY = getMinY();

		if (	(p.x >= minX) 	&&	 (p.x <= maxX)
			&&	(p.y >= minY)	&&	(p.y <= maxY))
			return true;
		else
			return false;
	//}
	//else
	//	return false;
}


int Segment::getMaxX(){
	if (p1.x >= p2.x)
		return p1.x;
	else
		return p2.x;
}

int Segment::getMinX(){
	if (p1.x <= p2.x)
		return p1.x;
	else
		return p2.x;
}


int Segment::getMaxY(){
	if(p1.y >= p2.y)
		return p1.y;
	else
		return p2.y;
}


int Segment::getMinY(){
	if(p1.y <= p2.y)
		return p1.y;
	else
		return p2.y;
}





