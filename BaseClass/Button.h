/*
 * Button.h
 *
 *  Created on: 30/ott/2012
 *      Author: enrico
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include "Quadrilateral.h"

class Button: public Quadrilateral {
public:
	Button();
	virtual ~Button();
	Button(int x,int y,int width, int height, string text);
	string getChunk();
	string getText();
private:
	string text;
};

#endif /* BUTTON_H_ */
