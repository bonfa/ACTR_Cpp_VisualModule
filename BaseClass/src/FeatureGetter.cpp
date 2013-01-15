/*
 * FeatureGetter.cpp
 *
 *  Created on: 29/ott/2012
 *      Author: enrico
 */

#include "FeatureGetter.h"
#define ARTOOLKIT 1

FeatureGetter::FeatureGetter() {
	withArToolkit = false;
	inputModule = new Input();
}

FeatureGetter::FeatureGetter(int i) {
	withArToolkit = true;
	//inputModule = new Input();
}

FeatureGetter::~FeatureGetter() {
	// TODO Auto-generated destructor stub
}



void FeatureGetter::updateImage(){
	//delete img;
	//img = inputModule->getImage("./shapes.png");
	//img = inputModule->getImage("./ellipses.jpg");
	//img = inputModule->getImage("./cndicdbnidvb.jpg");

	//img = inputModule->getImage("./images/01_02_1030797656577.bmp");
	//img = inputModule->getImage("./images/02_08_447099175936.bmp");
	//img = inputModule->getImage("./images/03_32_9007255098753112.bmp");
	//img = inputModule->getImage("./images/04_36_1478332047688192.bmp");
	//img = inputModule->getImage("./images/05_50_1548318539776144.bmp");
	//img = inputModule->getImage("./images/06_54_18023194906722704.bmp");
	//img = inputModule->getImage("./images/07_04_219903404277765.bmp");
	//img = inputModule->getImage("./images/08_06_114392163942656.bmp");
	//img = inputModule->getImage("./images/09_25_1337006283030553.bmp");
	//img = inputModule->getImage("./images/10_26_1548114663047204.bmp");
	//img = inputModule->getImage("./images/11_29_11261199174860888.bmp");
	//img = inputModule->getImage("./images/12_53_145525316052451328.bmp");		//TODO quadrato esterno
	//img = inputModule->getImage("./images/13_59_142118473433600.bmp");		//TODO	quadrato esterno
	//img = inputModule->getImage("./images/14_NA_498222760961.bmp");
	//img = inputModule->getImage("./images/15_NA_10793261728000.bmp");
	//img = inputModule->getImage("./images/16_NA_211142744211593.bmp");
	//img = inputModule->getImage("./images/17_NA_72480910316142593.bmp");		//TODO  quadrato esterno
	//img = inputModule->getImage("./images/18_NA_577445915800635392.bmp");
	//img = inputModule->getImage("./images/19_NA_580260668791324672.bmp");		//TODO	quadrato esterno
	//img = inputModule->getImage("./images/20_NA_583224952673546240.bmp");
	//img = inputModule->getImage("./images/21_NA_584350852048749056.bmp");
	//img = inputModule->getImage("./images/22_NA_865966563026534912.bmp");
	//img = inputModule->getImage("./images/23_NA_867083665762158848.bmp");
	img = inputModule->getImage("./images/24_M01_216770917518016516.bmp");
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


void FeatureGetter::setFeatureList(){
	featureExtractor = new FeatureExtractor(this->img);
	objectList = featureExtractor->getExtractedFeature();
	//return objectList;
/*
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
	//cout << getExtremeDistance(0,2) << endl << endl; //~17

	//Examples
	cout << "ROTATION" << endl;
	cout << getRotation(0) << endl;
	cout << getRotation(3) << endl
*/

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
	/**
	 * The distance between two objects is made in this way:
	 * 1) The straight line which passes between the centers of the two bounding boxes is calculated
	 * 2) The two points which are the results of the intersection between this line and one of the late of the bounding boxes are calculated
	 * 3) Calculation of the distance between these two new points
	 * */
	if (aIndex < 0)
		throw(InputException("negative index of vector [first element]"));
	if (this->outOfBound(aIndex))
		throw(InputException("index out of bound [first element]"));
	if (bIndex < 0)
		throw(InputException("negative index of vector [second element]"));
	if (this->outOfBound(bIndex))
		throw(InputException("index out of bound [second element]"));
	if (aIndex == bIndex)
		return 0;

	// Step 1 - Calculate the straight line which passes between the centers of the two bounding boxes
	Point aCenter = (objectList.at(aIndex))->getCenter();
	Point bCenter = (objectList.at(bIndex))->getCenter();
	Segment centerLine = Segment(aCenter,bCenter);

	//cout << aCenter.x << "-" << aCenter.y << endl;
	//cout << bCenter.x << "-" << bCenter.y << endl;

	//Step 2 - Get the edges of the two boxes
	std::vector<Segment> aEdges = (objectList.at(aIndex))->getBbox().getEdgesLine();
	std::vector<Segment> bEdges = (objectList.at(bIndex))->getBbox().getEdgesLine();
	//std::vector<Point> aPoints = (objectList.at(aIndex))->getBbox().getPoints();
	//std::vector<Point> bPoints = (objectList.at(bIndex))->getBbox().getPoints();

	//Step 3 - Calculate the intersection between the lines and the segments
	Point aIntersect,bIntersect;
	int numberofExceptions = 0;
	for(size_t i=0; i < aEdges.size(); i++){
		try{
			aIntersect = (aEdges.at(i)).getInterceptionPoint(centerLine);
			break;
		}
		catch (NotOverlappedSegmentException& e) {numberofExceptions++;}
	}
	//cout << "NoE = " <<numberofExceptions <<endl;
	if (numberofExceptions >= 4){
		throw  NotOverlappedSegmentException();
	}

	//numberofExceptions = 0;
	//cout << "NoE = " <<numberofExceptions <<endl;
	for(size_t i=0; i < bEdges.size(); i++){
		try{
			bIntersect = (bEdges.at(i)).getInterceptionPoint(centerLine);
			break;
		}
		catch (NotOverlappedSegmentException& e) {numberofExceptions++;}
	}
	//cout << "NoE = " <<numberofExceptions <<endl;
	if (numberofExceptions >= 4){
			throw  NotOverlappedSegmentException();
	}


	return myDistance(aIntersect,bIntersect);
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


double FeatureGetter::getRotation(int objIndex){
	if (objIndex < 0)
			throw(InputException("negative index of vector"));
	if (this->outOfBound(objIndex))
			throw(InputException("index out of bound"));

	Object * obj = objectList.at(objIndex);
	return obj->getRotation();
}



vector<string> FeatureGetter::getObjectChunkList(){
	vector<string> chunkList;
	for (unsigned int i=0; i<this->objectList.size();i++)
		chunkList.push_back(objectList.at(i)->getChunk());
	return chunkList;
}
