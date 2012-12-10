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
#include "utils.h"
#include "FeatureExtractor.h"
#include "MyPoint.h"



using namespace std;

class FeatureGetter {
public:
	FeatureGetter();
	virtual ~FeatureGetter(); //
	void updateImage();
	void startVideoCapture();
	void terminate();
	std::vector<Object *> getFeatureList();
	string isBigger(int aIndex, int bIndex);
	string getPosition (int aIndex,int bIndex);
	double getCenterDistance(int aIndex,int bIndex);
	double getExtremeDistance(int aIndex,int bIndex);
	//da cancellare una volta finito lo sviluppo
	void showImage();
	void showVideo();
private:
	Input *inputModule;
	FeatureExtractor *featureExtractor;
	cv::Mat img;
	cv::VideoCapture video;
	std::vector<Object *> objectList;
	bool outOfBound(unsigned int index);
	std::vector<Point> getPointList(Rect bbox);
};

#endif /* BASECLASS_H_ */
