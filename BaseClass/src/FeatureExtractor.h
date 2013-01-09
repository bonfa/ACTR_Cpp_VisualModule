/*
 * FeatureExtractor.h
 *
 *  Created on: 04/dic/2012
 *      Author: francesco
 *
 *	This class extract some features from the input image.
 *	The features are returned in an object list
 *	The extracted feature are:
 *		-) circles
 *		-) squares
 *		-) triangles
 *		-) color of a pixel
 *		-) color of an omogeneous area
 *
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
#include "MarkerDetector.h"

//todo: delete
typedef enum {QUADRILATERAL, TRIANGLE, CIRCLE} ShapeType;


class FeatureExtractor {
public:
	FeatureExtractor(cv::Mat img);
	FeatureExtractor::FeatureExtractor();
	/** Return the list of the recognized object in the image*/
	std::vector<Object *> getExtractedFeature();
	/** Return the color of a point*/
	string getPointColor(int x, int y);
	virtual ~FeatureExtractor();
private:
	/**Analizes the image and looks for circles in it. The circles found are added in the circleList*/
	void recognizeCircles();
	/** Analizes the image and looks for quadrilateral in it. The circles found are added in the quadrilateralList*/
	void recognizeSquares();
	/** Analizes the image and looks for triangles in it. The circles found are added in the triangleList*/
	void recognizeTriangles();
	/** Recognizes the QRCodes */
	void recognizeQRCodes();
	/** Receives as input the opencvValue of hue and returns it normalized in a "GimpLike" way*/
	double normHue(int hueVal);
	/** Receives as input the opencvValue of saturation or value and returns it normalized in a "GimpLike" way*/
	double normSV(int svVal);
	/** Starting from the "GimpLike" values of hue, saturation and value, it returns a string containing the name of the color referred by those three values*/
	string getColorString(double gimpHue, double gimpSaturation, double gimpValue);
	/** Returns the color of the region defined by the input points*/
	string getRegionColor(cv::vector<cv::Point> points);
	/** The input image */
	cv::Mat image;
	/** The list of all the quadrilaterals recognized in the input image*/
	std::vector<Quadrilateral *> quadrilateralList;
	/** The list of all the triangles recognized in the input image*/
	std::vector<Triangle *> triangleList;
	/** The list of all the circles recognized in the input image*/
	std::vector<Circle *> circleList;
	/** The list of all the objects recognized in the input image*/
	std::vector<Object *> objectList;
	/** The list of all the QRCodes recognized by ARToolkit*/
	std::vector<QRCode> qrList;

};

#endif /* FEATUREEXTRACTOR_H_ */
