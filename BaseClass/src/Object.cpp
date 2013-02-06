/*
 * Object.cpp
 *
 *  Created on: 30/ott/2012
 *      Author: enrico
 */

#include "Object.h"


Object::Object(bool att, double rot, Rect bb):attended(att), rotation(rot), bbox(bb){
	//TODO definire la notazione della rotazione
}

Object::Object(bool att, double rot, int xx, int yy, int widtha, int heighta):attended(att), rotation(rot), bbox(xx, yy, widtha, heighta){
	//Rect bbox = Rect(xx, yy, widtha, heighta);
}

Object::Object():attended(false), rotation(0) {
	// TODO Auto-generated destructor stub
}

Object::~Object() {
	// TODO Auto-generated destructor stub
}

Rect Object::getBbox(){
	return this->bbox;
}

/**
 * 1) control that the value of the bounding box are consistent
 * 2) create the bounding box
 * */
void Object::setBbox(int x, int y, int height, int width){
	if(x<0 || y < 0 || height <=0 || width <= 0)
		throw InputException("Negative values in the points coordinates");
	bbox = Rect(x, y, height, width);
}


Point Object::getCenter(){
	return center;
}

/**
 * The center of the object is set as the center of the bounding box
 * */
void Object::setCenter(){
	int xCenter = bbox.x + bbox.width/2;
	int yCenter = bbox.y + bbox.height/2;
	center = Point(xCenter,yCenter);
}


void Object::setColor(string color){
	this->color = color;
}


double Object::getRotation(){
	return rotation;
}

Json::Value Object::getJson(){
	//creating the bounding box
	Json::Value bbox;
	bbox["x1"] = this->bbox.x;
	bbox["y1"] = this->bbox.y;
	bbox["x2"] = this->bbox.x+this->bbox.width;
	bbox["y2"] = this->bbox.y+this->bbox.height;
	return bbox;
	
}

string Object::getChunk(){
	Json::FastWriter writer;
	return writer.write(this->getJson());
	/*string chunk = "{";
	chunk.append("\"type\": \"BoundingBox\",");
	chunk.append("\"x1\":");
	chunk.append("\"");
	chunk.append(intToString(this->bbox.x));
	chunk.append("\",");
	
	chunk.append("\"y1\":");
	chunk.append("\"");
	chunk.append(intToString(this->bbox.y));
	chunk.append("\",");
	
	chunk.append("\"x2\":");
	chunk.append("\"");
	chunk.append(intToString(this->bbox.x+this->bbox.width));
	chunk.append("\",");
	
	chunk.append("\"y2\":");
	chunk.append("\"");
	chunk.append(intToString(this->bbox.y+this->bbox.height));
	chunk.append("\"");
	chunk.append("}");*/
	
}

