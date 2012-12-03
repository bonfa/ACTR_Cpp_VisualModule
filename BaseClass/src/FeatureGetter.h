/*
 * BaseClass.h
 *
 *  Created on: 29/ott/2012
 *      Author: enrico
 */

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv/cxcore.h>
#include <iostream>

#ifndef BASECLASS_H_
#define BASECLASS_H_

using namespace std;

class FeatureGetter {
public:
	FeatureGetter();
	virtual ~FeatureGetter(); //
	cv::Mat getImage(cv::String path); //return image
	cv::VideoCapture getStream(); //return video
	void showVideo(cv::VideoCapture cap);
};

#endif /* BASECLASS_H_ */
