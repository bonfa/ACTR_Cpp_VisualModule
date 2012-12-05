/*
 * FeatureExtractor.cpp
 *
 *  Created on: 04/dic/2012
 *      Author: francesco
 */

#include "FeatureExtractor.h"
#include "Server.h"

#define MRG 25

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

}



void FeatureExtractor::recognizeTriangles(){

}


void FeatureExtractor::getExtractedFeature(){
	this->recognizeCircles();
	cout<<"color: "+this->getColor(100, 100)+"\n";
	cout<<"color: "+this->getColor(200, 100)+"\n";
	cout<<"color: "+this->getColor(100, 250)+"\n";
	cout<<"color: "+this->getColor(240, 240)+"\n";
	init(0);
}
