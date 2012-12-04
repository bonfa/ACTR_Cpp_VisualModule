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



class FeatureExtractor {
public:
	FeatureExtractor(cv::Mat img);
	void getExtractedFeature(); //@TODO: trasformare il tipo ritornato in una lista di oggetti
	virtual ~FeatureExtractor();
	string getColor(int x, int y, cv::Mat image);
private:
	cv::Point3_<uchar>* getPixel(int x, int y, cv::Mat image);
	void recognizeCircles();
	void recognizeSquares();
	void recognizeTriangles();
	cv::Mat image;

};

#endif /* FEATUREEXTRACTOR_H_ */
