/*
 * FeatureExtractor.cpp
 *
 *  Created on: 04/dic/2012
 *      Author: francesco
 */

#include "FeatureExtractor.h"

FeatureExtractor::FeatureExtractor(cv::Mat img) {
	image = img;
}



FeatureExtractor::~FeatureExtractor() {
	// TODO Auto-generated destructor stub
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
