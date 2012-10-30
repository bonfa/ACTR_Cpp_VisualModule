/*
 * BaseClass.h
 *
 *  Created on: 29/ott/2012
 *      Author: enrico
 */

#include <opencv/cv.h>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include <opencv/cxcore.h>
#include <iostream>

#ifndef BASECLASS_H_
#define BASECLASS_H_

using namespace cv;
using namespace std;

class BaseClass {
public:
	BaseClass();
	virtual ~BaseClass();
	Mat getImage(String path); //return image
	VideoCapture getStream(); //return video
	void showVideo(VideoCapture cap);
};

#endif /* BASECLASS_H_ */
