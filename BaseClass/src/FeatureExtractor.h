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
#include "Quadrilateral.h"
#include "Server.h"
#include "Triangle.h"
#include "Circle.h"
#include "Object.h"
#include "Blob.h"


typedef enum {QUADRILATERAL, TRIANGLE, CIRCLE} ShapeType;


class FeatureExtractor {
public:
	FeatureExtractor(cv::Mat img);
	std::vector<Object *> getExtractedFeature(); //@TODO: trasformare il tipo ritornato in una lista di oggetti
	virtual ~FeatureExtractor();
	string getPointColor(int x, int y);
private:
	void recognizeCircles();
	void recognizeSquares();
	void recognizeTriangles();
	double normHue(int hueVal);
	double normSV(int svVal);
	string getColorString(double gimpHue, double gimpSaturation, double gimpValue);
	string getRegionColor(cv::vector<cv::Point> points);
	cv::Mat image;
	std::vector<Quadrilateral *> quadrilateralList;
	std::vector<Triangle *> triangleList;
	std::vector<Circle *> circleList;
	std::vector<Object *> objectList;

};

#endif /* FEATUREEXTRACTOR_H_ */
