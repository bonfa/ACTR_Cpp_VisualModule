
#include "extractorUtils.h"


double angle( cv::Point pt1, cv::Point pt2, cv::Point pt0 ) {
    double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}



cv::vector<cv::vector<cv::Point> > squaresSort(cv::vector<cv::vector<cv::Point> > squareList)
{
	for ( unsigned int i = 0; i< squareList.size()-1; i++ ) {
		for ( unsigned int j = i+1; j< squareList.size(); j++ ) {
			if ((squareList.at(i).at(0).x > squareList.at(j).at(0).x)
					|| ((squareList.at(i).at(0).x == squareList.at(j).at(0).x) && (squareList.at(i).at(0).y > squareList.at(j).at(0).y))){
				cv::vector<cv::Point> t = squareList.at(j);
				squareList.at(j) = squareList.at(i);
				squareList.at(i) = t;
			}
		}
	}
	return squareList;
}


double myDistance(cv::Point a, cv::Point b){
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}


bool similar(cv::vector<cv::Point> a, cv::vector<cv::Point> b){
	double distance = myDistance(a.at(0),b.at(0));
	if (distance > 5)
		return false;

	double totalDistance = 0;
	for ( unsigned int i = 0; i< a.size(); i++ )
		totalDistance += myDistance(a.at(i),b.at(i));
	//totalDistance /= 4.0;
	if (totalDistance > 16)
		return false;

	double aArea = fabs(contourArea(cv::Mat(a)));
	double bArea = fabs(contourArea(cv::Mat(b)));
	if (aArea/bArea < 0.80  || aArea/bArea > 1.20)
		return false;

	double aPerimeter = fabs(cv::arcLength(a,1));
	double bPerimeter = fabs(cv::arcLength(b,1));
	if (aPerimeter/bPerimeter < 0.85  || aPerimeter/bPerimeter > 1.15)
		return false;

	return true;
}



cv::vector<cv::vector<cv::Point> > deleteOverlapped(cv::vector<cv::vector<cv::Point> > oldList){
	cv::vector<cv::vector<cv::Point> > withoutDuplicates;
	withoutDuplicates.push_back(oldList.at(0));

	for (unsigned int i = 1; i< oldList.size(); i++ ) {
		bool isSimilar = false;
		for ( unsigned int j = 0; j< withoutDuplicates.size(); j++ )
			if (similar(oldList.at(i),withoutDuplicates.at(j))){
				isSimilar = true;
				break;
			}
		if (isSimilar == false)
			withoutDuplicates.push_back(oldList.at(i));
	}
	return withoutDuplicates;
}




bool tooClose(cv::Point a, cv::Point b){
	if (myDistance(a,b) < 5)
			return true;
	return false;
}




bool isFalse(cv::vector<cv::Point> square){
	if (tooClose(square.at(0),square.at(1))
		||	tooClose(square.at(0),square.at(2))
		||	tooClose(square.at(0),square.at(3))
		||	tooClose(square.at(1),square.at(2))
		||	tooClose(square.at(1),square.at(3))
		||	tooClose(square.at(2),square.at(3)) )
		return true;
	return false;
}




cv::vector<cv::vector<cv::Point> > deleteFalseSquares(cv::vector<cv::vector<cv::Point> > oldList){
	cv::vector<cv::vector<cv::Point> > withoutFalseSquares;

	for (unsigned int i = 0; i< oldList.size(); i++ ){
		if (! isFalse(oldList.at(i))){
			withoutFalseSquares.push_back(oldList.at(i));
		}
	}

	return withoutFalseSquares;
}


cv::vector<cv::Point>  sort4PointsClockwise(cv::vector<cv::Point> points){
	FourPointsSorter *fps = new FourPointsSorter(points);
	points = fps->getSortedClockwise();
	return points;
}

//--------------------------------------------------------------------------------------------------

FourPointsSorter::FourPointsSorter(cv::vector<cv::Point> points_){
	points = points_;
	setCenter();
}


FourPointsSorter::~FourPointsSorter(){
	//@TODO
}


void FourPointsSorter::setCenter(){
	int xCenter = 0;
	int yCenter = 0;
	for (int i=0; i<4;i++){
		xCenter += points.at(i).x;
		yCenter += points.at(i).y;
	}
	center = cv::Point(xCenter/4,yCenter/4);
}


cv::vector<cv::Point> FourPointsSorter::getSortedClockwise(){
	for ( unsigned int i = 0; i< points.size(); i++ ) {
			for ( unsigned int j = i+1; j< points.size(); j++ ) {
				if (lessPoint(points.at(j),points.at(i))){
					cv::Point t = points.at(i);
					points.at(i) = points.at(j);
					points.at(j) = t;
				}
			}
		}
	return points;
}




bool FourPointsSorter::lessPoint(cv::Point a, cv::Point b)
{
    if (a.x >= 0 && b.x < 0)
        return true;
    if (a.x == 0 && b.x == 0)
        return a.y > b.y;

    // compute the cross product of vectors (center -> a) x (center -> b)
    int det = (a.x-center.x) * (b.y-center.y) - (b.x - center.x) * (a.y - center.y);
    if (det < 0)
        return true;
    if (det > 0)
        return false;

    // points a and b are on the same line from the center
    // check which point is closer to the center
    int d1 = (a.x-center.x) * (a.x-center.x) + (a.y-center.y) * (a.y-center.y);
    int d2 = (b.x-center.x) * (b.x-center.x) + (b.y-center.y) * (b.y-center.y);
    return d1 > d2;
}
