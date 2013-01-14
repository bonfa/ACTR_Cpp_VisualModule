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
	char * filename = (char *)malloc(path.length()+1);
	strcpy(filename, path.c_str());
	if (!fileExists(filename))
		throw InputException("error in the input image");
	else {
		img = cv::imread(path);
		return img;
	}
	//TODO: raise an exception if the image does not exists

}


cv::VideoCapture Input::getStream(){
	cv::VideoCapture cap(0);
	//TODO: raise an exception if there is something wrong
	return cap;
}





Input::~Input() {
	// TODO Auto-generated destructor stub
}

