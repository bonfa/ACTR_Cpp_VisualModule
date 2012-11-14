/*
 * Rect.h
 *
 *  Created on: 13/nov/2012
 *      Author: francesco
 */

#ifndef RECT_H_
#define RECT_H_

#include "BaseClassException.h"

class Rect {
public:
	Rect();
	Rect(int x, int y, int height, int width);
	virtual ~Rect();
	int x;
	int y;
	int height;
	int width;
};

#endif /* RECT_H_ */
