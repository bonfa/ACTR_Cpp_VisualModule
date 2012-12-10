/*
 * BaseClass.cpp
 *
 *  Created on: 29/ott/2012
 *      Author: enrico
 */

#include "FeatureGetter.h"


FeatureGetter::FeatureGetter() {
	inputModule = new Input();
}


FeatureGetter::~FeatureGetter() {
	// TODO Auto-generated destructor stub
}



void FeatureGetter::updateImage(){
	//delete img;
	//img = inputModule->getImage("./shapes.png");
	img = inputModule->getImage("./01_02_1030797656577.bmp");
}


void FeatureGetter::showImage(){
	cv::imshow("finestra",img);
	cv::waitKey(0);
}


void FeatureGetter::startVideoCapture(){
	video = inputModule->getStream();

}

void FeatureGetter::showVideo(){
	cv::Mat edges;
	cv::namedWindow("edges",1);

	for(;;)
	{
		cv::Mat frame;
		video >> frame; // get a new frame from camera
		cv::cvtColor(frame, edges, CV_BGR2GRAY);
		cv::GaussianBlur(edges, edges, cv::Size(7,7), 1.5, 1.5);
		cv::Canny(edges, edges, 0, 50, 3);
		cv::imshow("edges", edges);
		if(cv::waitKey(30) >= 0) break;
	}
}


void FeatureGetter::terminate(){
	cv::destroyAllWindows();
}


std::vector<Object *> FeatureGetter::getFeatureList(){
	featureExtractor = new FeatureExtractor(this->img);
	objectList = featureExtractor->getExtractedFeature();

	//Examples
	cout << isBigger(0,0) << endl; //equal
	cout << isBigger(0,1) << endl; //smaller
	cout << isBigger(7,0) << endl << endl; //bigger

	//Examples
	cout << getPosition(2,2) <<endl;  //same x - same y
	cout << getPosition(0,2) <<endl;  //left - above
	cout << getPosition(2,0) <<endl << endl;  //right - below

	//Examples
	cout << getCenterDistance(2,2) << endl;  //0
	cout << getCenterDistance(0,2) << endl << endl;  //~431

	//Examples
	cout << getExtremeDistance(0,0) << endl; //0
	cout << getExtremeDistance(0,5) << endl; //~17

	return objectList;
}


string FeatureGetter::isBigger(int aIndex,int bIndex){
	if (aIndex < 0)
		throw(InputException("negative index of vector [first element]"));
	if (this->outOfBound(aIndex))
		throw(InputException("index out of bound [first element]"));
	if (bIndex < 0)
		throw(InputException("negative index of vector [second element]"));
	if (this->outOfBound(bIndex))
		throw(InputException("index out of bound [second element]"));

	double aArea = ((Blob *)objectList.at(aIndex))->getArea();
	double bArea = ((Blob *)objectList.at(bIndex))->getArea();

	if (aArea == bArea)
		return "equal";
	else if (aArea > bArea)
		return "bigger";
	else
		return "smaller";
}



bool FeatureGetter::outOfBound(unsigned int index){
	return (index >= this->objectList.size());
}


string FeatureGetter::getPosition(int aIndex,int bIndex){
	if (aIndex < 0)
		throw(InputException("negative index of vector [first element]"));
	if (this->outOfBound(aIndex))
		throw(InputException("index out of bound [first element]"));
	if (bIndex < 0)
		throw(InputException("negative index of vector [second element]"));
	if (this->outOfBound(bIndex))
		throw(InputException("index out of bound [second element]"));

	int ax = ((Blob *)objectList.at(aIndex))->getBbox().x;
	int ay = ((Blob *)objectList.at(aIndex))->getBbox().y;

	int bx = ((Blob *)objectList.at(bIndex))->getBbox().x;
	int by = ((Blob *)objectList.at(bIndex))->getBbox().y;

	string horizontalPosition, verticalPosition;
	if(ax < bx)
		horizontalPosition = "left";
	else if (ax == bx)
		horizontalPosition = "same x";
	else
		horizontalPosition = "right";

	if(ay < by)
		verticalPosition = "above";
	else if (ay == by)
		verticalPosition = "same y";
	else
		verticalPosition = "below";

	return horizontalPosition + " - " + verticalPosition;
}




double FeatureGetter::getCenterDistance(int aIndex,int bIndex){
	if (aIndex < 0)
		throw(InputException("negative index of vector [first element]"));
	if (this->outOfBound(aIndex))
		throw(InputException("index out of bound [first element]"));
	if (bIndex < 0)
		throw(InputException("negative index of vector [second element]"));
	if (this->outOfBound(bIndex))
		throw(InputException("index out of bound [second element]"));

	Point aCenter = (objectList.at(aIndex))->getCenter();
	Point bCenter = (objectList.at(bIndex))->getCenter();


	return myDistance(aCenter,bCenter);
}



double FeatureGetter::getExtremeDistance(int aIndex,int bIndex){
	if (aIndex < 0)
		throw(InputException("negative index of vector [first element]"));
	if (this->outOfBound(aIndex))
		throw(InputException("index out of bound [first element]"));
	if (bIndex < 0)
		throw(InputException("negative index of vector [second element]"));
	if (this->outOfBound(bIndex))
		throw(InputException("index out of bound [second element]"));

	std::vector<Point> aPoints = this->getPointList((objectList.at(aIndex))->getBbox());
	std::vector<Point> bPoints = this->getPointList((objectList.at(bIndex))->getBbox());

	//@todo:change this method with something smarter
	//for the moment this method returns the minimum of all the distances between the points of the first bbox and the points ot the second bounding box
	double minDistance = myDistance(aPoints.at(0),bPoints.at(0));
	for (size_t i=0; i < aPoints.size(); i++)
		for (size_t j=0; j < bPoints.size(); j++){
			double distance = myDistance(aPoints.at(i),bPoints.at(j));
			if (distance < minDistance)
				minDistance = distance;
		}
	return minDistance;
}


std::vector<Point> FeatureGetter::getPointList(Rect bbox){
	std::vector<Point> pointList;
	Point p1 = Point(bbox.x,bbox.y);
	Point p2 = Point(bbox.x+bbox.width,bbox.y);
	Point p3 = Point(bbox.x+bbox.width,bbox.y+bbox.height);
	Point p4 = Point(bbox.x,bbox.y+bbox.height);

	pointList.push_back(p1);
	pointList.push_back(p2);
	pointList.push_back(p3);
	pointList.push_back(p4);
	return pointList;
}





