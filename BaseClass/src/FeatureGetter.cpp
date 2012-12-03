/*
 * BaseClass.cpp
 *
 *  Created on: 29/ott/2012
 *      Author: enrico
 */

#include "FeatureGetter.h"


FeatureGetter::FeatureGetter() {

	// TODO Auto-generated constructor stub

}

FeatureGetter::~FeatureGetter() {
	// TODO Auto-generated destructor stub
}

//FIXME : sostituire le cv:String con le stringhe di c++
cv::Mat FeatureGetter::getImage(string path){
	cv::Mat img;

	img=cv::imread(path);     // carica l'immagine

	return img;
} //return image


void FeatureGetter::showVideo(cv::VideoCapture cap){
	cv::Mat edges;
	cv::namedWindow("edges",1);

	for(;;)
	{
		cv::Mat frame;
		cap >> frame; // get a new frame from camera
		cv::cvtColor(frame, edges, CV_BGR2GRAY);
		cv::GaussianBlur(edges, edges, cv::Size(7,7), 1.5, 1.5);
		cv::Canny(edges, edges, 0, 50, 3);
		cv::imshow("edges", edges);
		if(cv::waitKey(30) >= 0) break;
	}

}


cv::VideoCapture FeatureGetter::getStream(){
	cv::VideoCapture cap(0);
	return cap;
} //return video

