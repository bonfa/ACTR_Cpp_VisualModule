/*
 * FeatureExtractor.h
 *
 *  Created on: 04/dic/2012
 *      Author: francesco
 */

using namespace std;

#ifndef FEATUREEXTRACTOR_H_
#define FEATUREEXTRACTOR_H_

#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include "utils.h"
#include "extractorUtils.h"



class FeatureExtractor {
public:
	FeatureExtractor(cv::Mat img);
	void getExtractedFeature(); //@TODO: trasformare il tipo ritornato in una lista di oggetti
	virtual ~FeatureExtractor();
	string getPointColor(int x, int y);
private:
	cv::Point3_<uchar>* getPixel(int x, int y);
	void recognizeCircles();
	void recognizeSquares();
	void recognizeTriangles();
	double normColor(int hueVal);
	string getColorString(double gimpHueValue);
	cv::Mat image;

};

#endif /* FEATUREEXTRACTOR_H_ */
