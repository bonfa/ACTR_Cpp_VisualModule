/*
 * Input.h
 *
 *  Created on: 03/dic/2012
 *      Author: francesco
 */

#ifndef INPUT_H_
#define INPUT_H_

#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>
#include <iostream>
#include <string>
using namespace std;


class Input {
public:
	Input();
	cv::Mat getImage(cv::String path); //return image
	cv::VideoCapture getStream(); //return video
	virtual ~Input();
};

#endif /* INPUT_H_ */
