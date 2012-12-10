/*
 * utils.h
 *
 *  Created on: 02/nov/2012
 *      Author: enrico
 */

#ifndef UTILS_H_
#define UTILS_H_

#define MAX_X 1
#define MAX_Y 2
#define MIN_X 3
#define MIN_Y 4


#include <opencv/cv.h>
#include <vector>
#include <math.h>
#include "MyPoint.h"
#include "StraightLine.h"



int getMinMax(const std::vector<Point>& coords, int type);
std::vector<Point> Sort4PointsClockwise(std::vector<Point> points);
bool inLinePoints(int ax, int ay, int bx, int by, int cx, int cy );
double erone(Point a, Point b, Point c);
double myDistance(Point a, Point b);







#endif /* UTILS_H_ */
