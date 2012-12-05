/*
 * BaseClass.h
 *
 *  Created on: 29/ott/2012
 *      Author: enrico
 */


#ifndef BASECLASS_H_
#define BASECLASS_H_

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv/cxcore.h>

#include <iostream>
#include "Input.h"
#include "FeatureExtractor.h"


using namespace std;

class FeatureGetter {
public:
	FeatureGetter();
	virtual ~FeatureGetter(); //
	void updateImage();
	void startVideoCapture();
	void terminate();
	void getFeatureList(); 	//@TODO: da trasformare il tipo ritornato in vector<Objects>
	//da cancellare una volta finito lo sviluppo
	void showImage();
	void showVideo();
private:
	Input *inputModule;
	FeatureExtractor *featureExtractor;
	cv::Mat img;
	cv::VideoCapture video;
};

#endif /* BASECLASS_H_ */
