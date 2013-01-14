/*
 * Rect.cpp
 *
 *  Created on: 13/nov/2012
 *      Author: francesco
 */

#include "Rect.h"

Rect::Rect(){
	x = 0;
	y = 0;
	height = 0;
	width = 0;
}

/**
 * Constructor
 * 1) check that the coordinates of the point are not negative
 * 2) check that the width and the height are positive
 * 3) creates the rectangle
 * */
Rect::Rect(int x_, int y_, int height_, int width_) {
	//TODO mettere a posto questo controllo!!!
	if(x_< 0 || y_ < 0 || height_ <= 0 || width_ <= 0)
				throw InputException(("Negative values in the coordinates"));
	x = x_;
	y = y_;
	height = height_;
	width = width_;
}


/**
 * Constructor
 * 1) check that the coordinates of the point are not negative
 * 2) check that the width and the height are positive
 * 3) creates the rectangle
 * */
Rect::Rect(Point p, int height_, int width_){
	if(p.x < 0)
		throw InputException(("Negative values in the coordinates [p.x]"));
	if(p.y < 0)
		throw InputException(("Negative values in the coordinates [p.y]"));
	if(height_ <= 0)
		throw InputException(("Negative values in the coordinates [height]"));
	if(width_ <= 0)
		throw InputException(("Negative values in the coordinates [width_]"));

	x = p.x;
	y = p.y;

	height = height_;
	width = width_;
}


bool Rect::operator==(const Rect &other) const {
	return ((this->x==other.x) && (this->y == other.y) && (this->height == other.height) && (this->width == other.width));
}


Rect::~Rect() {

}



std::vector<Segment> Rect::getEdgesLine(){
	std::vector<Segment> lineList;

	std::vector<Point> pointList = this->getPoints();

	try{
		Segment line1 = Segment(pointList.at(0),pointList.at(1));
		Segment line2 = Segment(pointList.at(1),pointList.at(2));
		Segment line3 = Segment(pointList.at(2),pointList.at(3));
		Segment line4 = Segment(pointList.at(3),pointList.at(0));

		lineList.push_back(line1);
		lineList.push_back(line2);
		lineList.push_back(line3);
		lineList.push_back(line4);
	}
	catch (InputException &e) {
		throw InputException("Coincident Points [default constructor]");
	}

	return lineList;
}


std::vector<Point> Rect::getPoints(){
	std::vector<Point> pointList;
	Point p1 = Point(this->x,this->y);
	Point p2 = Point(this->x+this->width,this->y);
	Point p3 = Point(this->x+this->width,this->y+this->height);
	Point p4 = Point(this->x,this->y+this->height);

	pointList.push_back(p1);
	pointList.push_back(p2);
	pointList.push_back(p3);
	pointList.push_back(p4);

	return pointList;
}


