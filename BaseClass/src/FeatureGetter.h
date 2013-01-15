/*
 * FeatureGetter.h
 *
 *  Created on: 29/ott/2012
 *      Author: enrico
 *
 * This class is the interface for the server.
 * It initializes the input.
 * It processes the input images to extract the features.
 * It returns some strings which contains information about the image processed
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
#include "StraightLine.h"
#include "Segment.h"
#include "FeatureGetterExceptions.h"



using namespace std;

class FeatureGetter {
public:
	FeatureGetter();
	FeatureGetter(int i);
	virtual ~FeatureGetter();
	/** Update the input image to be processed*/
	void updateImage();
	/** Starts the video capture*/
	void startVideoCapture();
	/** TODO: ??*/
	void terminate();
	/** Extract the list of the recognized objects*/
	void setFeatureList();
	/** Returns a string which tells if the object in the first position has area greater less or equal
	 * to the area in the second position*/
	string isBigger(int aIndex, int bIndex);
	/** Return the relative position of the first object corresponding to the second one*/
	string getPosition (int aIndex,int bIndex);
	/** Return the distance between the centers of the two objects indexed by the two indexes in input*/
	double getCenterDistance(int aIndex,int bIndex);
	/** Gives the extreme distance of two object.
	 *  ATTENTION: check how this method works*/
	double getExtremeDistance(int aIndex,int bIndex);
	/** Gives the rotation of shape in counterclockwise starting from the horizontal position of an object.
	 *  ATTENTION: check how this method works*/
	double getRotation(int index);
	/** Return the list of all the chunks in a JSON way */
	vector<string> getObjectChunkList();


	//TODO: da cancellare una volta finito lo sviluppo
	void showImage();
	void showVideo();
private:
	/** The input module*/
	Input *inputModule;
	/** The feature extractor*/
	FeatureExtractor *featureExtractor;
	/** The input image*/
	cv::Mat img;
	/** The input video*/
	cv::VideoCapture video;
	/** The object list*/
	std::vector<Object *> objectList;
	/** Return true if the index of the object list is >= of the length of the number of objects*/
	bool outOfBound(unsigned int index);
	/** Returns the list of the points of a rect TODO: delete this method*/
	std::vector<Point> getPointList(Rect bbox);
	/** Define if the imput method is Artoolkit */
	bool withArToolkit;
};

#endif /* BASECLASS_H_ */
