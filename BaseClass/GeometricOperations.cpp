/*
 * GeometricOperations.cpp
 *
 *  Created on: 02/nov/2012
 *      Author: francesco
 */


#include "GeometricOperations.h"

bool inLinePoints(int ax, int ay, int bx, int by, int cx, int cy ){

	StraightLine *line = new StraightLine(ax,ay,bx,by);
	return line->doesPointBelongTo(cx,cy);
}



