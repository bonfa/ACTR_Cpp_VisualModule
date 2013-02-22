/*
 * Button.h
 *
 *  Created on: 30/ott/2012
 *      Author: enrico
 *
 *  This class represent a button.
 *  A button is a rectangle with some text inside.
 *
 *  It is defined by a point, which is the starting point of the rectangle
 *  and the width and the height of the rectangle itself.
 *  In a common 2D space, the point is the bottom-left point of the rectangle.
 *  In a 2D space as the one defined by the opencv Mat it is the top left point of the rectangle.
 *  @ATTENTION: the coordinates must not be negative
 */

#ifndef BUTTON_H_
#define BUTTON_H_



#include "Quadrilateral.h"


class Button: public Quadrilateral {
public:
	virtual ~Button();
	Button(int x,int y,int width, int height, string text);
	/** Returns a string which contains the basic information about the button*/
	string getChunk();
	/** Returns a string which contains the text of the button */
	string getText();
protected:
	/** Creates a Json object that contains the basic information about the quadrilateral*/
	virtual Json::Value getJson();
private:
	/** The text of the button */
	string text;
};

#endif /* BUTTON_H_*/
