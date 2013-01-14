/*
 * ocvutils.h
 *
 *  Created on: 05/dic/2012
 *      Author: francesco
 *
 *  Utilities used by "FeatureExtractor" and "FeatureGetter" classes
 */

#ifndef OCVUTILS_H_
#define OCVUTILS_H_

#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include "utils.h"

//TODO: trasformare in classi

/**TODO documentation
 * TODO testing*/
double angle( cv::Point pt1, cv::Point pt2, cv::Point pt0 );

/** Gives the distance between two 2D points */
double myDistance(cv::Point a, cv::Point b);

/** return true if the two shapes (defined as sequences of points) are too similar.
 * This method is used to delete similar shapes which differ only for a few things.
 *
 * For example, a shape and another one obtained adding +1 to all the pixel coordinates are similar.
 *
 *   */
bool similar(cv::vector<cv::Point> a, cv::vector<cv::Point> b);

/** Return true if the two points are very close one to each other
 * */
bool tooClose(cv::Point a, cv::Point b);

/** Return true if the square is not a real square.
 * For example, if two vertices are too close one each other, the shape is not a square.
 * */
bool isFalse(cv::vector<cv::Point> square);

/** Return true if the triangle is a real square.
 * For example, if two vertices are too close one each other, the shape is not a triangle.
 * TODO rename this method: it is just a threshold on the area*/
bool isTriangle(cv::vector<cv::Point> terna);

/** deletes the overlapped squares from the input square list
 * */
cv::vector<cv::vector<cv::Point> > deleteOverlapped(cv::vector<cv::vector<cv::Point> > oldList);

/** Sort the points of every square in the list putting as the first element the point nearest
 * to the origin (0,0) and then following the clockwise order.
 * If there are two points with the same distance, it puts the one with minimum x.
 * */
cv::vector<cv::vector<cv::Point> > squaresSort(cv::vector<cv::vector<cv::Point> > squareList);

/** delete the false squares from the input square list
 * */
cv::vector<cv::vector<cv::Point> > deleteFalseSquares(cv::vector<cv::vector<cv::Point> > oldList);

/**  Sort the points of the list starting from the first element nearest to the origin (0,0)
 * and then following the clockwise order.
 * If there are two points with the same distance, the first point is the one with minimum x.
 * */
cv::vector<cv::Point> sort4PointsClockwise(cv::vector<cv::Point> points);

/** delete the false triangles from the input triangle list
 * */
cv::vector<cv::vector<cv::Point> > deleteFalseTriangles(cv::vector<cv::vector<cv::Point> > oldList);


/** This class receives in input a vector of points
 * 	and gives some functions that sort them in different orders.
 *
 * 	The possible orders are:
 * 	1) clockwise starting from the point nearest to the origin (0,0).
 * 		If there are two points with the same distance, the first point is the one with minimum x.
 *
 *  */
class FourPointsSorter{
public:
	FourPointsSorter(cv::vector<cv::Point> points_);
	~FourPointsSorter();
	/** Return the ponts sorted as described in 1)*/
	cv::vector<cv::Point> getSortedRotatedClockwise();
private:
	/** The point which is the center of the four points*/
	cv::Point center;
	/** The point list*/
	cv::vector<cv::Point> points;
	/** Calculate the center of the point list.
	 * The x of the center is the average of the x of the points in the list.
	 * The y of the center is the average of the y of the points in the list.
	 * */
	void setCenter();
	/** Sort the point clockwise*/
	void sortClockWise();
	/**TODO: change the name of this method
	 * Rotate until the point with smaller distance from the origin is in first position*/
	void rotateUntilMinXFirst();
	/** Return the position of the first point*/
	int getFirstPointPosition();
	/** return the distance of a point from the origin*/
	double getDistance(cv::Point p);
	/** Rotates the point clockwise of the input shiftValue*/
	void rotate(int shiftValue);
	/** ??  //TODO*/
	bool lessPoint(cv::Point a, cv::Point b);
};




#endif /* OCVUTILS_H_ */
