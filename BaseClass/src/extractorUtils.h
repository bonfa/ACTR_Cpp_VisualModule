/*
 * ocvutils.h
 *
 *  Created on: 05/dic/2012
 *      Author: francesco
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

double angle( cv::Point pt1, cv::Point pt2, cv::Point pt0 );
cv::vector<cv::vector<cv::Point> > squaresSort(cv::vector<cv::vector<cv::Point> > squareList);
double myDistance(cv::Point a, cv::Point b);
bool similar(cv::vector<cv::Point> a, cv::vector<cv::Point> b);
cv::vector<cv::vector<cv::Point> > deleteOverlapped(cv::vector<cv::vector<cv::Point> > oldList);
bool tooClose(cv::Point a, cv::Point b);
bool isFalse(cv::vector<cv::Point> square);
cv::vector<cv::vector<cv::Point> > deleteFalseSquares(cv::vector<cv::vector<cv::Point> > oldList);
cv::vector<cv::Point> sort4PointsClockwise(cv::vector<cv::Point> squareList);


class FourPointsSorter{
public:
	FourPointsSorter(cv::vector<cv::Point> points_);
	~FourPointsSorter();
	cv::vector<cv::Point> getSortedClockwise();
private:
	cv::Point center;
	cv::vector<cv::Point> points;
	void setCenter();
	bool lessPoint(cv::Point a, cv::Point b);
};




#endif /* OCVUTILS_H_ */
