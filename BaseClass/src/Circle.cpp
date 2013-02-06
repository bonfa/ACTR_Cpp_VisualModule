/*
 * Circle.cpp
 *
 *  Created on: 31/ott/2012
 *      Author: enrico
 */

#include "Circle.h"
#include <math.h>


/**
 * Constructor
 * 1) check that all the coordinates are not negative
 * 2) create the circle
 * 3) set the area
 * 4) set the bounding box
 * 5) the center of the bounding box is the center of the circle
 * */
Circle::Circle(int rad, int x, int y) {
	//TODO mettere a posto questo controllo!!!!
	if(x < 0 || y < 0 || rad <= 0 || x-rad <0 || y-rad <0)
		throw InputException(("Negative values in the points coordinates"));
	radius = rad;
	center.x = x;
	center.y = y;
	area = rad * rad * M_PI;
	setBbox(x-rad, y-rad, 2*rad, 2*rad);
	this->setRotation();
}

Json::Value Circle::getJson(){
	Json::Value obj;
	Json::Value c;
	c["x"] = this->center.x;
	c["y"] = this->center.y;
	Json::Value rad;
	rad["rad"] = this->radius;
	//creating the vertices' array
	Json::Value vertices(Json::arrayValue);
	vertices.append(c);
	vertices.append(rad);
	//put all together in the hierarchy
	obj["Bbox"]=Object::getJson();
	obj["Vertices"]=vertices;
	obj["Type"]="Circle";
	obj["Color"]=this->color;
	return obj;
}

string Circle::getChunk(){
	Json::FastWriter writer;
	return writer.write(this->getJson());
}


int Circle::getXCenter(){
	return this->center.x;
}


int Circle::getYCenter(){
	return this->center.y ;
}

Point Circle::getCenter(){
	return this->center;
}

int Circle::getRadius(){
	return this->radius;
}

void Circle::setRotation(){
	//A circle does not have a rotation parameter
	rotation = 0;
}

Circle::~Circle() {

}
