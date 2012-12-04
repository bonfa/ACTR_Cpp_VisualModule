/*
 * FeatureExtractor.cpp
 *
 *  Created on: 04/dic/2012
 *      Author: francesco
 */

#include "FeatureExtractor.h"
#define MRG 25

FeatureExtractor::FeatureExtractor(cv::Mat img) {
	image = img;
}



FeatureExtractor::~FeatureExtractor() {
	// TODO Auto-generated destructor stub
}


cv::Point3_<uchar>* FeatureExtractor::getPixel(int x, int y, cv::Mat image){
	return image.ptr<cv::Point3_<uchar> >(y,x); //Point3_<uchar>* p
}


string FeatureExtractor::getColor(int x, int y, cv::Mat image){

	cv::Point3_<uchar>* p;
	p = getPixel(x, y, image);

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
	cv::Mat grey;
	/// Reduce the noise so we avoid false circle detection
  cv::GaussianBlur( image, grey, cv::Size(9, 9), 2, 2 );

  cv::vector<cv::Vec3f> circles;

  /// Apply the Hough Transform to find the circles
  cv::HoughCircles( grey, circles, CV_HOUGH_GRADIENT, 1, grey.rows/8, 200, 100, 0, 0 );

  /// Draw the circles detected
  for( size_t i = 0; i < circles.size(); i++ )
  {
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
}
