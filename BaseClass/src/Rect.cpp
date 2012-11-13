/*
 * Rect.cpp
 *
 *  Created on: 13/nov/2012
 *      Author: francesco
 */

#include "Rect.h"

Rect::Rect() {
	// TODO Auto-generated constructor stub

}

Rect::Rect(int x_, int y_, int height_, int width_) {
	if(x_< 0 || y_ < 0 || height_ <= 0 || width_ <= 0)
				throw InputException(("Negative values in the coordinates"));
	x = x_;
	y = y_;
	height = height_;
	width = width_;
}

Rect::~Rect() {
	// TODO Auto-generated destructor stub
}

