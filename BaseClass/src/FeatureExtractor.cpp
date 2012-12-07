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



string FeatureExtractor::getPointColor(int x, int y){
	// Convert image to HSV.
	cv::Mat hsv;
	cv::cvtColor(image, hsv, CV_BGR2HSV);

	cv::Mat hslChannels[3];
	cv::split(hsv, hslChannels);

	cv::Mat hueLevel = hslChannels[0];

	//cv::Rect roi(x-3,y-3,5,5);
	//cv::Mat colorBlob = hueLevel(roi);
	//printf("%.2f\n",normColor(colorBlob.data[colorBlob.step*2+2]));

	double hue = this->normHue(hueLevel.data[hueLevel.step*y+x]);
	double sat = this->normSV(hslChannels[1].data[hslChannels[1].step*y+x]);
	double val = this->normSV(hslChannels[2].data[hslChannels[2].step*y+x]);

	printf("%.2f\n",hue);
	printf("%.2f\n",sat);
	printf("%.2f\n",val);
	return this->getColorString(hue,sat,val);
}


string FeatureExtractor::getRegionColor(cv::vector<cv::Point> points){
	//imposto il roi nella bounding box della forma
	cv::Rect boundingBox = boundingRect(cv::Mat(points));
	cv::Mat boundedImg = image(boundingBox);

	//converto l'immagine in immagine binaria.
	cv::Mat binary,gray;
	cv::cvtColor(boundedImg, gray, CV_BGR2GRAY);
	int thresholdValue = 128;
	cv::threshold(gray, binary, thresholdValue, 255, CV_THRESH_BINARY);
	//cv::imshow( "bin", binary );
	//cv::waitKey(0);

	//converto la boundedImg in HSV
	cv::Mat hsvRegion;
	cv::cvtColor(boundedImg, hsvRegion, CV_BGR2HSV);
	cv::Mat hsvChannels[3];
	cv::split(hsvRegion, hsvChannels);

	//Uso l'immagine binaria come flag. L'oggetto è nero.
	//Faccio la media dei valori di saturazione dei pixel
	double totalPixel = 0;
	double regionH = 0;
	double regionS = 0;
	double regionV = 0;

	for (int i=0;i<binary.rows;i++)
		for (int j=0;j<binary.cols;j++)
			if(binary.data[binary.step*i+j] < 10) {
				totalPixel += 1;
				regionH += hsvChannels[0].data[hsvChannels[0].step*i+j];
				regionS += hsvChannels[1].data[hsvChannels[1].step*i+j];
				regionV += hsvChannels[2].data[hsvChannels[2].step*i+j];
			}
	regionH /= totalPixel;
	regionS /= totalPixel;
	regionV /= totalPixel;

	double hue = this->normHue(regionH);
	double sat = this->normSV(regionS);
	double val = this->normSV(regionV);

	printf("%.2f\n",regionH);
	return this->getColorString(hue,sat,val);
}


double FeatureExtractor::normHue(int hueVal){
	return ((double)hueVal*360.0/180.0);
}

double FeatureExtractor::normSV(int svVal){
	return ((double)svVal*100.0/255.0);
}

string FeatureExtractor::getColorString(double gimpHue, double gimpSaturation, double gimpValue){
	if ((gimpValue >= 0) && (gimpValue <= 30))
		return "black";
	else if (((gimpValue >= 95) && (gimpValue <= 100)) && ((gimpSaturation>=0) && (gimpSaturation<=5)))
		return "white";
	else if (((gimpValue >= 30) && (gimpValue <= 60)) && ((gimpSaturation>=5) && (gimpSaturation<=15)))
		return "gray";
	else if ((gimpHue < 15.0) || ((gimpHue > 330.0) && (gimpHue < 360.0)))
		return "red";
	else if(gimpHue < 45.0)
		return "orange";
	else if(gimpHue < 65.0)
		return "yellow";
	else if(gimpHue < 140.0)
		return "green";
	else if(gimpHue < 210.0)
		return "cyan";
	else if(gimpHue < 250.0)
		return "blue";
	else if(gimpHue < 280.0)
		return "violet";
	else if(gimpHue < 330.0)
		return "pink";
	else return "unknown";
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

						//if (maxCosine < 0.3)
								squares.push_back(approx);
					}
			}
		}
	}

	//disegno i quadrati
	cv::Mat rects;
	rects = cv::Mat::zeros(image.rows,image.cols,CV_8UC3);


	//ordino in verso antiorario ogni quaterna di vettori
	for ( unsigned int i = 0; i< squares.size(); i++ ) {
		squares.at(i) = sort4PointsClockwise(squares.at(i));
	}


	//controllo che non ci siano quadrati con punti quasi coincidenti
	squares = deleteFalseSquares(squares);

	//ordino secondo il vettore secondo la coordinata x e poi y del primo punto
	squares = squaresSort(squares);

	//elimino i quadrati sovrapposti
	squares = deleteOverlapped(squares);



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
	// create the structure that contains the triangles
	cv::vector<cv::vector<cv::Point> > triangles;

	// blur will enhance edge detection
	cv::Mat blurred(image);
	cv::medianBlur(image, blurred, 9);

	// create two gray images
	cv::Mat gray0(blurred.size(), CV_8U), gray;
	// create the structure that contains contours
	cv::vector<cv::vector<cv::Point> > contours;

	// find triangles in every color plane of the image
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
					if (approx.size() == 3 && cv::isContourConvex(cv::Mat(approx)))
					{

						//@todo: capire a cosa serve il controllo sull'angolo (per adesso è commentato e il programma va bene lo stesso)
						double maxCosine = 0;

						for (int j = 2; j < 5; j++)
						{
								double cosine = fabs(angle(approx[j%4], approx[j-2], approx[j-1]));
								maxCosine = MAX(maxCosine, cosine);
						}

						//if (maxCosine < 0.3)
							triangles.push_back(approx);
					}
			}
		}
	}

	//disegno i triangoli
	cv::Mat rects;
	rects = cv::Mat::zeros(image.rows,image.cols,CV_8UC3);


	//ordino in verso antiorario ogni quaterna di vettori
	for ( unsigned int i = 0; i< triangles.size(); i++ ) {
		triangles.at(i) = sort4PointsClockwise(triangles.at(i));
	}


	//controllo che non ci siano quadrati con punti quasi coincidenti
	triangles = deleteFalseTriangles(triangles);

	//ordino secondo il vettore secondo la coordinata x e poi y del primo punto
	triangles = squaresSort(triangles);

	//elimino i quadrati sovrapposti
	triangles = deleteOverlapped(triangles);

	for (unsigned int i = 0; i< triangles.size(); i++ ) {

		// draw contour
		cv::drawContours(rects, triangles, i, cv::Scalar(255,0,0), 1, 8, std::vector<cv::Vec4i>(), 0, cv::Point()); //blue

		// draw bounding rect
		cv::Rect rect = boundingRect(cv::Mat(triangles[i]));
		cv::rectangle(rects, rect.tl(), rect.br(), cv::Scalar(0,255,0), 2, 8, 0); //verde

		printf("F %d: ",i+1);
		for (unsigned int j=0;j<triangles.at(i).size();j++){
			printf("(%d,%d)  ",triangles.at(i).at(j).x,triangles.at(i).at(j).y);
		}
		printf("\n\n");
	}


	cv::imshow("triangles",rects);
	cv::waitKey(0);
}


void FeatureExtractor::getExtractedFeature(){
	//this->recognizeCircles();


	cout<<"color: "+this->getPointColor(100, 100)+"\n";   //rosso
	cout<<"color: "+this->getPointColor(200, 100)+"\n";		//verde
	cout<<"color: "+this->getPointColor(100, 250)+"\n";		//blue
	cout<<"color: "+this->getPointColor(240, 240)+"\n";		//giallo
	cout<<"color: "+this->getPointColor(118, 42)+"\n";		//bianco
	cout<<"color: "+this->getPointColor(580,367)+"\n";		//nero

	//init(0);
	cv::vector<cv::Point> p1;
	p1.push_back(cv::Point(77,42));
	p1.push_back(cv::Point(29,127));
	p1.push_back(cv::Point(127,130));
	cout<<"color: "+this->getRegionColor(p1)+"\n";	//rosso

	//this->recognizeTriangles();
	//this->recognizeSquares();
}







