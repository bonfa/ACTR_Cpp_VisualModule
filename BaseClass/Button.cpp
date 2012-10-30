/*
 * Button.cpp
 *
 *  Created on: 30/ott/2012
 *      Author: enrico
 */

#include "Button.h"

Button::Button() {
	// TODO Auto-generated constructor stub

}

Button::~Button() {
	// TODO Auto-generated destructor stub
}

Button::Button(int x,int y,int width, int height, string txt){
	a = cvPoint(x, y);
	b = cvPoint(x + width, y);
	c = cvPoint(x + width, y+ height);
	d = cvPoint(x, y+ height);
	text = txt;
}


string Button::getChunk(){
	return "cianc, bottone\n";
}

double Button::getArea(){
	return (b.x - a.x)*(c.y - d.y);
}

string Button::getText(){
	return text;
}
