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
#include <cmath>
#include "StraightLine.h"


int getMinMax(const std::vector<CvPoint>& coords, int type);
void Sort4PointsClockwise(std::vector<CvPoint> points);
bool inLinePoints(int ax, int ay, int bx, int by, int cx, int cy );
double erone(CvPoint a, CvPoint b, CvPoint c);

#endif /* UTILS_H_ */
