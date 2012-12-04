/*
 * FeatureExtractor.h
 *
 *  Created on: 04/dic/2012
 *      Author: francesco
 */

#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>
#include <iostream>
#include <string>
using namespace std;
using namespace cv;

#ifndef FEATUREEXTRACTOR_H_
#define FEATUREEXTRACTOR_H_



class FeatureExtractor {
public:
	FeatureExtractor();
	virtual ~FeatureExtractor();
	string getColor(int x, int y, Mat image);
private:
	Point3_<uchar>* getPixel(int x, int y, Mat image);
};

#endif /* FEATUREEXTRACTOR_H_ */
