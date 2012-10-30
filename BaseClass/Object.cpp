/*
 * Object.cpp
 *
 *  Created on: 30/ott/2012
 *      Author: enrico
 */

#include "Object.h"

Object::Object(bool att, double rot, CvRect bb){
	attended = att;
	rotation = rot;
	bbox = bb;
}

Object::Object(bool att, double rot, int xx, int yy, int widtha, int heighta){
	CvRect bbox = cvRect(xx, yy, widtha, heighta);
	attended = att;
	rotation = rot;
}

Object::Object() {
	// TODO Auto-generated destructor stub
}



Object::~Object() {
	// TODO Auto-generated destructor stub
}

