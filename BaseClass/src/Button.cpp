/*
 * Button.cpp
 *
 *  Created on: 30/ott/2012
 *      Author: enrico
 */

#include "Button.h"


Button::~Button() {

}

/**
 * Constructor
 * 1) check that the coordinates of the point are not negative
 * 2) check that the width and the height are positive
 * 3) check that the string is not empty
 * 4) creates the button
 * 5) set the bounding box
 * 6) set the center of the bounding box
 * */
Button::Button(int x,int y, int height, int width, string txt) :text(""){
	if(x< 0|| y < 0 || width <1 || height < 1)
		throw InputException(("Inammissible values in the points coordinates"));
	if(txt.length()<1)
		throw InputException(("Text is empty"));

	a = Point(x, y);
	b = Point(x + width, y);
	c = Point(x + width, y+ height);
	d = Point(x, y+ height);
	text = txt; //TODO bisogna usare lo strcpy?
	area = (b.x - a.x)*(c.y - d.y);

	setBbox(x, y, height, width);
	this->setCenter();
}

Json::Value Button::getJson(){
	Json::Value obj = Quadrilateral::getJson();
	obj["text"]=this->text;
	return obj;
}

string Button::getChunk(){
	Json::FastWriter writer;
	return writer.write(this->getJson());
}

string Button::getText(){
	return text;
}
