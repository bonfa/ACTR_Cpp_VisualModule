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
#define EPSILON 0.00001


#include <opencv/cv.h>
#include <vector>
#include <math.h>
#include <ios>
#include "MyPoint.h"
#include "StraightLine.h"
#include "FeatureGetterExceptions.h"
#include <fstream>



int getMinMax(const std::vector<Point>& coords, int type);
std::vector<Point> Sort4PointsClockwise(std::vector<Point> points);
double erone(Point a, Point b, Point c);


/**
 * Given three 2D points, this method calculates if all of them
 * belong to the same line
 * */
bool inLinePoints(int ax, int ay, int bx, int by, int cx, int cy );



/**
 * Given two 2D points, this method calculates the distance between them.
 * The distance is calculated as
 *
 * sqrt((a.x-b.x)^2 + (a.y-b.y)^2)
 *
 * @author: francesco
 *
 * */
double myDistance(Point a, Point b);


/**
 * This method tells if two double values are equal under a certain values
 *
 * The precision is determined by a variable called EPSILON which
 * is defined externally to the function
 * */
bool areSame(double a, double b);


/**
 * This method returns the minimum value of the list
 * */
double getMin(const std::vector<double>& values);



/** Return true if the file exists, otherwise false*/
bool fileExists(char * path);


#endif /* UTILS_H_ */
