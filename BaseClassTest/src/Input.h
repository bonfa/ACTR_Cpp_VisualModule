/*
 * Input.h
 *
 *  Created on: 03/dic/2012
 *      Author: francesco
 *
 *  This class represents a generic input for the image or for the video.
 *
 *  The input can be:
 *  1) an image;
 *  2) a video stream captured by a webcam;
 */

#ifndef INPUT_H_
#define INPUT_H_

#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>
#include <iostream>
#include <string>
#include "FeatureGetterExceptions.h"
#include "utils.h"
#include <string.h>

using namespace std;


class Input {
public:
	Input();
	/**return the image at that path*/
	cv::Mat getImage(cv::String path);
	/**return the video captured by the webcam*/
	cv::VideoCapture getStream();
	virtual ~Input();
};

#endif /* INPUT_H_ */
