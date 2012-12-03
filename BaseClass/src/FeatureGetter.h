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
#include "Input.h"

#ifndef BASECLASS_H_
#define BASECLASS_H_

using namespace std;

class FeatureGetter {
public:
	FeatureGetter();
	virtual ~FeatureGetter(); //
	void updateImage();
	void startVideoCapture();
	void terminate();
	//da cancellare una volta finito lo sviluppo
	void showImage();
	void showVideo();
private:
	Input *inputModule;
	cv::Mat img;
	cv::VideoCapture video;
};

#endif /* BASECLASS_H_ */
