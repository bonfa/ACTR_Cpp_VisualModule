/*
 * Input.cpp
 *
 *  Created on: 03/dic/2012
 *      Author: francesco
 */

#include "Input.h"


Input::Input() {
	// TODO Auto-generated constructor stub

}



cv::Mat Input::getImage(string path){
	cv::Mat img;

	img=cv::imread(path);     // carica l'immagine

	return img;
} //return image


cv::VideoCapture Input::getStream(){
	cv::VideoCapture cap(0);
	return cap;
} //return video





Input::~Input() {
	// TODO Auto-generated destructor stub
}

