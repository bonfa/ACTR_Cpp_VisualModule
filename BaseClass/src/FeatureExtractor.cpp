/*
 * FeatureExtractor.cpp
 *
 *  Created on: 04/dic/2012
 *      Author: francesco
 */

#include "FeatureExtractor.h"
#define MRG 25


double angle( cv::Point pt1, cv::Point pt2, cv::Point pt0 ) {
    double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}



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
	/*
	cv::Mat edge,color,gray;

	/// Convert it to gray
	cv::cvtColor( image, gray, CV_BGR2GRAY );

	cv::Canny(gray, edge, 50, 200, 3);
	cv::cvtColor(edge, color, CV_GRAY2BGR);

	cv::vector<cv::Vec4i> lines;
	cv::HoughLinesP(edge, lines, 1, CV_PI/180, 30, 35, 3);
	for( size_t i = 0; i < lines.size(); i++ ) 	{
		cv::Vec4i l = lines[i];
		cv::line( color, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(0,0,255), 1, CV_AA);
	}

	cv::imshow("detected lines", color);
	cv::waitKey(0);
	*/



	cv::vector<cv::vector<cv::Point> > squares;
    // blur will enhance edge detection
	cv::Mat blurred(image);
	cv::medianBlur(image, blurred, 9);

	cv::Mat gray0(blurred.size(), CV_8U), gray;
	cv::vector<cv::vector<cv::Point> > contours;

	// find squares in every color plane of the image
	for (int c = 0; c < 3; c++)
	{
		int ch[] = {c, 0};
		cv::mixChannels(&blurred, 1, &gray0, 1, ch, 1);

		// try several threshold levels
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
			for (size_t i = 0; i < contours.size(); i++) {
					// approximate contour with accuracy proportional to the contour perimeter
					cv::approxPolyDP(cv::Mat(contours[i]), approx, arcLength(cv::Mat(contours[i]), true)*0.02, true);

					// Note: absolute value of an area is used because area may be positive or negative - in accordance with the
					// contour orientation
					if (approx.size() == 4 && fabs(contourArea(cv::Mat(approx))) > 1000 && cv::isContourConvex(cv::Mat(approx)))
					{
						//@todo: capire a cosa serve il controllo sull'angolo (per adesso è commentato e il programma va bene lo stesso)
							double maxCosine = 0;

							for (int j = 2; j < 5; j++)
							{
									double cosine = fabs(angle(approx[j%4], approx[j-2], approx[j-1]));
									maxCosine = MAX(maxCosine, cosine);
							}

							//if (maxCosine < 0.3)
									squares.push_back(approx);
					}
			}
		}
	}

	//printf("ciao");

	//disegno i quadrati
	cv::Mat rects;
	rects = cv::Mat::zeros(image.rows,image.cols,CV_8UC3);

	//@todo: controllare doppioni nella lista di punti



	for ( int i = 0; i< squares.size(); i++ ) {
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
		for (int j=0;j<squares.at(i).size();j++){
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
	this->recognizeSquares();
}







