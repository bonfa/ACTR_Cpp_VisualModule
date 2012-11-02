/*
 * Object.cpp
 *
 *  Created on: 30/ott/2012
 *      Author: enrico
 */

#include "Object.h"


Object::Object(bool att, double rot, CvRect bb):attended(att), rotation(rot), bbox(bb){
	//TODO definire la notazione della rotazione
}

Object::Object(bool att, double rot, int xx, int yy, int widtha, int heighta):attended(att), rotation(rot){
	CvRect bbox = cvRect(xx, yy, widtha, heighta);
}

Object::Object():attended(false), rotation(0) {
	// TODO Auto-generated destructor stub
}

Object::~Object() {
	// TODO Auto-generated destructor stub
}

void Object::setBbox(int x, int y, int height, int width){
	if(x<0 || y < 0 || height <=0 || width <= 0)
		throw inputException("Negative values in the points coordinates");
	bbox = cvRect(x, y, height, width);
}
