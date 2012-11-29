/*
 * BaseClass.cpp
 *
 *  Created on: 29/ott/2012
 *      Author: enrico
 */

#include "BaseClass.h"
/*

int main(){
	BaseClass *b = new BaseClass();

	//imshow("finestra",b->getImage("./lena.jpg"));
	//waitKey(0);
	
	VideoCapture cap = b->getStream();
	b->showVideo(cap);


}*/

BaseClass::BaseClass() {

	// TODO Auto-generated constructor stub

}

BaseClass::~BaseClass() {
	// TODO Auto-generated destructor stub
}

//FIXME : sostituire le cv:String con le stringhe di c++
cv::Mat BaseClass::getImage(string path){
	cv::Mat img;

	img=cv::imread(path);     // carica l'immagine

	return img;
} //return image


void BaseClass::showVideo(cv::VideoCapture cap){
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


cv::VideoCapture BaseClass::getStream(){
	cv::VideoCapture cap(0);
	return cap;
} //return video

