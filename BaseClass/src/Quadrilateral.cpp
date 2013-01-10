/*
 * Quadrilateral.cpp
 *
 *  Created on: 30/ott/2012
 *      Author: enrico
 */

#include "Quadrilateral.h"


Quadrilateral::Quadrilateral() {
	// TODO Auto-generated constructor stub
}

Quadrilateral::~Quadrilateral() {
}

/**
 * Constructor
 * 1) check that all the coordinates are not negative
 * 2) check that the points are not on the same line
 * 3) sort the vertices following the clockwise order
 * 4) creates the quadrilateral
 * 5) set the area
 * 6) set the bounding box
 * 7) set the center of the bounding box
 * */
Quadrilateral::Quadrilateral(int ax,int ay,int bx,int by,int cx,int cy,int dx,int dy){
	if(ax<0 || ay<0 || bx<0 || by<0 || cx<0 || cy<0 || dx<0 || dy<0)
		throw InputException("Negative coordinate");

	if (inLinePoints(ax,ay,bx,by,cx,cy) || inLinePoints(ax,ay,bx,by,dx,dy) || inLinePoints(dx,dy,bx,by,cx,cy) ||inLinePoints(ax,ay,cx,cy,dx,dy))
		throw InputException("More than two points on the same line");

	int maxX, minX, maxY, minY;

	a = Point(ax, ay);
	b = Point(bx, by);
	c = Point(cx, cy);
	d = Point(dx, dy);

	std::vector<Point> coords;
	coords.push_back(a);
	coords.push_back(b);
	coords.push_back(c);
	coords.push_back(d);

	Sort4PointsClockwise(coords);

	a = coords.at(0);
	b = coords.at(1);
	c = coords.at(2);
	d = coords.at(3);

	area = erone(a, b, c) + erone(a, c , d);

	maxX = getMinMax(coords, MAX_X);
	maxY = getMinMax(coords, MAX_Y);
	minX = getMinMax(coords, MIN_X);
	minY = getMinMax(coords, MIN_Y);

	setBbox(minX, minY, maxY - minY, maxX-minX);
	this->setCenter();
	this->setRotation();
}


Point Quadrilateral::getA(){
	return this->a;
}



Point Quadrilateral::getB(){
	return this->b;
}



Point Quadrilateral::getC(){
	return this->c;
}


Point Quadrilateral::getD(){
	return this->d;
}


void Quadrilateral::setRotation(){
	//TODO --> testing
	//Get the equations of the edges
	std::vector<Segment> edgeList = this->getEdgesLine();

	//Create a list which contains the artg(m) of every non vertical line
	std::vector<double> rotationList;
	for (unsigned int i=0; i<edgeList.size(); i++){
		//exclude the vertical lines (which have the maximum slope)
		if (!((edgeList.at(i)).isVertical())){
			double atg = atan2((edgeList.at(i)).getSlope(),1);
			//when the angle is < 0, add PI to make it positive
			if (atg < 0)
				atg += M_PI;
			rotationList.push_back(atg);
		}
	}
	rotation = getMin(rotationList);
}


std::vector<Segment> Quadrilateral::getEdgesLine(){
	std::vector<Segment> lineList;

	Segment line1 = Segment(a,b);
	Segment line2 = Segment(b,c);
	Segment line3 = Segment(c,d);
	Segment line4 = Segment(d,a);

	lineList.push_back(line1);
	lineList.push_back(line2);
	lineList.push_back(line3);
	lineList.push_back(line4);

	return lineList;
}

string Quadrilateral::getChunk(){
	return "cianc, Quadrilateral\n";
}

