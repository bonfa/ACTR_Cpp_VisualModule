/*
 * Input.cpp
 *
 *  Created on: 03/dic/2012
 *      Author: francesco
 */

#include "Input.h"


Input::Input() {
}



cv::Mat Input::getImage(string path){
	cv::Mat img;

	img = cv::imread(path);
	//TODO: raise an exception if the image does ont exists
	return img;
}


cv::VideoCapture Input::getStream(){
	cv::VideoCapture cap(0);
	//TODO: raise an exception if there is something wrong
	return cap;
}





Input::~Input() {
	// TODO Auto-generated destructor stub
}

