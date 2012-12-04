/*
 * BaseClass.cpp
 *
 *  Created on: 29/ott/2012
 *      Author: enrico
 */

#include "FeatureGetter.h"


FeatureGetter::FeatureGetter() {
	inputModule = new Input();
}


FeatureGetter::~FeatureGetter() {
	// TODO Auto-generated destructor stub
}



void FeatureGetter::updateImage(){
	//delete img;
	img = inputModule->getImage("./shapes.png");
}


void FeatureGetter::showImage(){
	cv::imshow("finestra",img);
	cv::waitKey(0);
}


void FeatureGetter::startVideoCapture(){
	video = inputModule->getStream();

}

void FeatureGetter::showVideo(){
	cv::Mat edges;
	cv::namedWindow("edges",1);

	for(;;)
	{
		cv::Mat frame;
		video >> frame; // get a new frame from camera
		cv::cvtColor(frame, edges, CV_BGR2GRAY);
		cv::GaussianBlur(edges, edges, cv::Size(7,7), 1.5, 1.5);
		cv::Canny(edges, edges, 0, 50, 3);
		cv::imshow("edges", edges);
		if(cv::waitKey(30) >= 0) break;
	}
}


void FeatureGetter::terminate(){
	cv::destroyAllWindows();
}


