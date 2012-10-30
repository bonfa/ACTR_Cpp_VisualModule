/*
 * BaseClass.cpp
 *
 *  Created on: 29/ott/2012
 *      Author: enrico
 */

#include "BaseClass.h"

int main(){
	BaseClass *b = new BaseClass();

	//imshow("finestra",b->getImage("./lena.jpg"));
	//waitKey(0);

	VideoCapture cap = b->getStream();
	b->showVideo(cap);

}

BaseClass::BaseClass() {

	// TODO Auto-generated constructor stub

}

BaseClass::~BaseClass() {
	// TODO Auto-generated destructor stub
}


Mat BaseClass::getImage(String path){
	Mat img;

	img=imread(path);     // carica l'immagine

	return img;
} //return image


void BaseClass::showVideo(VideoCapture cap){
	Mat edges;
	namedWindow("edges",1);

	for(;;)
	{
		Mat frame;
		cap >> frame; // get a new frame from camera
		cvtColor(frame, edges, CV_BGR2GRAY);
		GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
		Canny(edges, edges, 0, 50, 3);
		imshow("edges", edges);
		if(waitKey(30) >= 0) break;
	}

}


VideoCapture BaseClass::getStream(){
	VideoCapture cap(0);
	return cap;
} //return video

