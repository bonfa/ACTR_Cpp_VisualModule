/*
 * Button.cpp
 *
 *  Created on: 30/ott/2012
 *      Author: enrico
 */

#include "Button.h"


Button::~Button() {

}

Button::Button(int x,int y, int height, int width, string txt) :text(""){
	if(x< 0|| y < 0 || width <1 || height < 1)
		throw InputException(("Inammisible values in the points coordinates"));
	if(txt.length()<1)
		throw InputException(("Text is empty"));

	a = cvPoint(x, y);
	b = cvPoint(x + width, y);
	c = cvPoint(x + width, y+ height);
	d = cvPoint(x, y+ height);
	text = txt; //TODO bisogna usare lo strcpy?
	area = (b.x - a.x)*(c.y - d.y);

	setBbox(x, y, height, width);
}


string Button::getChunk(){
	return "cianc, bottone\n";
}

string Button::getText(){
	return text;
}
