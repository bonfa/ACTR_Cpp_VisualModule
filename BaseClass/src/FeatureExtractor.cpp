/*
 * FeatureExtractor.cpp
 *
 *  Created on: 04/dic/2012
 *      Author: francesco
 */

#include "FeatureExtractor.h"
#include "Server.h"

#define MRG 25


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
			if ((squareList.at(
					i).at(0).x > squareList.at(j).at(0).x)
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


bool similar(vector<cv::Point> a, vector<cv::Point> b){
	if (myDistance(a.at(0),b.at(0)) > 4)
		return false;

	double totalDistance = 0;
	for ( unsigned int i = 0; i< a.size(); i++ )
		totalDistance += myDistance(a.at(i),b.at(i));
	totalDistance /= 4;
	if (totalDistance > 2)
		return false;

	double aArea = fabs(contourArea(cv::Mat(a)));
	double bArea = fabs(contourArea(cv::Mat(b)));
	if (aArea/bArea < 0.95  || aArea/bArea > 1.05)
		return false;

	double aPerimeter = fabs(cv::arcLength(a,1));
	double bPerimeter = fabs(cv::arcLength(b,1));
	if (aPerimeter/bPerimeter < 0.95  || aPerimeter/bPerimeter > 1.05)
		return false;

	return true;
}


/*
cv::vector<cv::vector<cv::Point> > deleteOverlapped(cv::vector<cv::vector<cv::Point> > oldList){
	for ( unsigned int i = 0; i< oldList.size()-1; i++ ) {
			for ( unsigned int j = i+1; j< oldList.size(); j++ )
				if (similar(oldList.at(i),oldList.at(j)))
					oldList.erase(j);
	}
	return oldList;
}*/
cv::vector<cv::vector<cv::Point> > deleteOverlapped(cv::vector<cv::vector<cv::Point> > squareList){
	/*for ( unsigned int i = 0; i< squareList.size()-1; i++ )
		for ( unsigned int j = i+1; j< squareList.size(); j++ )
			if (similar(squareList.at(i),squareList.at(j)))
				squareList.erase(j);*/
	return squareList;
}









FeatureExtractor::FeatureExtractor(cv::Mat img) {
	image = img;
}



FeatureExtractor::~FeatureExtractor() {
	// TODO Auto-generated destructor stub
}


cv::Point3_<uchar>* FeatureExtractor::getPixel(int x, int y){
	return image.ptr<cv::Point3_<uchar> >(y,x); //Point3_<uchar>* p
}

string FeatureExtractor::getColor(int x, int y){
	// Convert image to HSV.



	cv::Mat hsl;

	cv::cvtColor(image, hsl, CV_RGB2HSV);

	cv::Mat hslChannels[3];
	cv::split(hsl, hslChannels);

	hslChannels[0];



	/*



	cv::Mat hsvImage;
	cvtColor( image, hsvImage, CV_BGR2HSV );
	cv::imshow("d",hsvImage);
	cv::waitKey();
	CvScalar s;
	s=cv::get2D(imgRGB,i,j);

	p = hsvImage.ptr<cv::Point3_<uchar> >(y,x);
	// extract hue
	/*cv::Mat* hueImage = cv::createImage( size, 8, 1 );
	cv::setImageCOI( hsvImage, 1 );
	cv::copy( hsvImage, hueImage );

	cv::imshow("der",hueImage);
	cv::waitKey();*/

/*
	cv::Mat hsv;
	cv::Mat hue;
	cv::Mat sat;
	cv::Mat val;

	cvtColor( image, hsv, CV_BGR2HSV );

	cv::imshow("d",hsv);
	cv::waitKey();

	hue.create( hsv.size(), hsv.depth() );
	int ch[] = { 0, 0 };
	mixChannels( &hsv, 1, &hue, 1, ch, 1 );



*/
	if(hslChannels[1].at<uchar>(x,y) <30.0 *180.0 /360.0 )
		return "red";
	else if(hslChannels[0].at<uchar>(x,y)<90*180.0 /360.0)
		return "yellow";
	else if(hslChannels[0].at<uchar>(x,y)<150*180.0 /360.0)
		return "green";
	else if(hslChannels[0].at<uchar>(x,y)<210*180.0 /360.0)
		return "cyan";
	else if(hslChannels[0].at<uchar>(x,y)<270*180.0 /360.0)
		return "blue";
	else if(hslChannels[0].at<uchar>(x,y)<330*180.0 /360.0)
			return "pink";
	else return "unknown";

	//cout << p->y ;
	//cout << p->z ;
	/*
	if(p->z > 250 - MRG && p->y < MRG && p->x < MRG)
		return "red";
	else if(p->z < MRG && p->y < 167 + MRG && p->y > 167 - MRG && p->x > 230 - MRG)
		return "cyan";
	else if(p->z > 250 - MRG && p->y < 219 + MRG && p->y > 219 - MRG && p->x < MRG)
		return "yellow";
	else if(p->z < MRG && p->y < 103 + MRG && p->y > 103 - MRG && p->x < 169 + MRG && p->x > 169 - MRG)
		return "blue";
	else if(p->z > 255 - MRG && p->y < 153 + MRG && p->y > 153 - MRG && p->x < 51 + MRG && p->x > 51 - MRG)
		return "orange";
	else if(p->z > 34 - MRG && p->z < 34 + MRG && p->y < 232 + MRG && p->y > 232 - MRG && p->x < 62 + MRG && p->x > 62 - MRG)
		return "green";
	else if(p->z < 50 && p->y < 50 && p->x < 50 && p->z + p->y + p->x < 120)
		return "black";
	/*
	p->x //B
	p->y //G
	p->z //R */
	return "unknown";
}


void FeatureExtractor::recognizeCircles(){
	cv::Mat gray;

	/// Convert it to gray
	cv::cvtColor( image, gray, CV_BGR2GRAY );


	/// Reduce the noise so we avoid false circle detection
	cv::GaussianBlur( gray, gray, cv::Size(9, 9), 2, 2 );

	cv::vector<cv::Vec3f> circles;

	/// Apply the Hough Transform to find the circles
	cv::HoughCircles( gray, circles, CV_HOUGH_GRADIENT, 1, gray.rows/8, 200, 100, 0, 0 );

	/// Draw the circles detected
	for( size_t i = 0; i < circles.size(); i++ ) {
		cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		// circle center
		circle( image, center, 3, cv::Scalar(0,255,0), -1, 8, 0 );
		// circle outline
		circle( image, center, radius, cv::Scalar(0,0,255), 3, 8, 0 );
	}

	/// Show your results
	cv::namedWindow( "Hough Circle Transform Demo", CV_WINDOW_AUTOSIZE );
	cv::imshow( "Hough Circle Transform Demo", image );

	cv::waitKey(0);
}



void FeatureExtractor::recognizeSquares(){
	// create the structure that contains the squares
	cv::vector<cv::vector<cv::Point> > squares;

	// blur will enhance edge detection
	cv::Mat blurred(image);
	cv::medianBlur(image, blurred, 9);

	// create two gray images
	cv::Mat gray0(blurred.size(), CV_8U), gray;
	// create the structure that contains contours
	cv::vector<cv::vector<cv::Point> > contours;

	// find squares in every color plane of the image (only gray plane)
	for (int c = 0; c < 3; c++)
	{
		int ch[] = {c, 0};
		// extract the single colour level in gray0
		cv::mixChannels(&blurred, 1, &gray0, 1, ch, 1);

		// try several threshold levels (0,1 and 2)
		const int threshold_level = 2;
		for (int l = 0; l < threshold_level; l++)
		{
			// Use Canny instead of zero threshold level!
			// Canny helps to catch squares with gradient shading
			if (l == 0)
			{
				Canny(gray0, gray, 10, 20, 3); //

				// Dilate helps to remove potential holes between edge segments
				cv::dilate(gray, gray, cv::Mat(), cv::Point(-1,-1));
			}
			else
			{
				gray = gray0 >= (l+1) * 255 / threshold_level;
			}

			// Find contours and store them in a list
			cv::findContours(gray, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

			// Test contours
			cv::vector<cv::Point> approx;
			cout << contours.size();
			for (size_t i = 0; i < contours.size(); i++) {
					// approximate contour with accuracy proportional to the contour perimeter
					cv::approxPolyDP(cv::Mat(contours[i]), approx, arcLength(cv::Mat(contours[i]), true)*0.02, true);

					// Note: absolute value of an area is used because area may be positive or negative - in accordance with the
					// contour orientation
					//if (approx.size() == 4 && fabs(contourArea(cv::Mat(approx))) > 1000 && cv::isContourConvex(cv::Mat(approx)))
					if (approx.size() == 4 && cv::isContourConvex(cv::Mat(approx)))
					{

						//@todo: capire a cosa serve il controllo sull'angolo (per adesso è commentato e il programma va bene lo stesso)
						double maxCosine = 0;

						for (int j = 2; j < 5; j++)
						{
								double cosine = fabs(angle(approx[j%4], approx[j-2], approx[j-1]));
								maxCosine = MAX(maxCosine, cosine);
						}

						if (maxCosine < 0.3)
								squares.push_back(approx);
					}
			}
		}
	}

	//printf("ciao");

	//disegno i quadrati
	cv::Mat rects;
	rects = cv::Mat::zeros(image.rows,image.cols,CV_8UC3);


	//ordino in verso antiorario ogni quaterna di vettori
	for ( unsigned int i = 0; i< squares.size(); i++ ) {
		squares.at(i) = Sort4cvPointsClockwise(squares.at(i));
	}

	//ordino secondo il vettore secondo la coordinata x e poi y del primo punto
	squares = squaresSort(squares);

	//elimino i quadrati sovrapposti
	squares = deleteOverlapped(squares);

	//@todo: controllare doppioni nella lista di punti


	for (unsigned int i = 0; i< squares.size(); i++ ) {

		// draw contour
		cv::drawContours(rects, squares, i, cv::Scalar(255,0,0), 1, 8, std::vector<cv::Vec4i>(), 0, cv::Point()); //blue

		// draw bounding rect
		cv::Rect rect = boundingRect(cv::Mat(squares[i]));
		cv::rectangle(rects, rect.tl(), rect.br(), cv::Scalar(0,255,0), 2, 8, 0); //verde

		// draw rotated rect
		/*
		cv::RotatedRect minRect = minAreaRect(cv::Mat(squares[i]));
		cv::Point2f rect_points[4];
		minRect.points( rect_points );
		for ( int j = 0; j < 4; j++ ) {
			cv::line( rects, rect_points[j], rect_points[(j+1)%4], cv::Scalar(0,0,255), 1, 8 ); // red
		}*/
		printf("F %d: ",i+1);
		for (unsigned int j=0;j<squares.at(i).size();j++){
			printf("(%d,%d)  ",squares.at(i).at(j).x,squares.at(i).at(j).y);
		}
		printf("\n\n");
	}


	cv::imshow("quadr",rects);
	cv::waitKey(0);
}



void FeatureExtractor::recognizeTriangles(){

}


void FeatureExtractor::getExtractedFeature(){
	this->recognizeCircles();
	/*
	cout<<"color: "+this->getColor(100, 100)+"\n";
	cout<<"color: "+this->getColor(200, 100)+"\n";
	cout<<"color: "+this->getColor(100, 250)+"\n";
	cout<<"color: "+this->getColor(240, 240)+"\n";*/
	init(0);
	this->recognizeSquares();
}







