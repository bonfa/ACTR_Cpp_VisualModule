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
	std::vector<Quadrilateral> quadrilateralList;
	std::vector<Triangle> triangleList;
	std::vector<Circle> circleList;
	findMarkers = false;
}

//Serve ad iniziare l'estrazione di features nel caso in cui si usi ARToolkit
FeatureExtractor::FeatureExtractor(){
	//image = NULL;
	std::vector<Quadrilateral> quadrilateralList;
	std::vector<Triangle> triangleList;
	std::vector<Circle> circleList;
	findMarkers = true;
}


FeatureExtractor::~FeatureExtractor() {
}


/** Converts the image in HSV, normalize the value as Gimp and then recognize the color
 * starting from the new values*/
string FeatureExtractor::getPointColor(int x, int y){
	// Convert image to HSV.
	cv::Mat hsv;
	cv::cvtColor(image, hsv, CV_BGR2HSV);

	//Split image into 3 separates channels H,S,V
	cv::Mat hslChannels[3];
	cv::split(hsv, hslChannels);

	//Normalize Opencv values as Gimp values
	double hue = this->normHue(hslChannels[0].data[hslChannels[0].step*y+x]);
	double sat = this->normSV(hslChannels[1].data[hslChannels[1].step*y+x]);
	double val = this->normSV(hslChannels[2].data[hslChannels[2].step*y+x]);

	//printf("%.2f\n",hue);
	//printf("%.2f\n",sat);
	//printf("%.2f\n",val);

	//returns the correct string
	return this->getColorString(hue,sat,val);
}

/** Converts the image in grayscale
 *  apply a threshold to distinguish foreground to background
 *  Using the thresholded image as a foreground background map,
 *  it averages all the values of HSV of the object.
 *  Then it calls the function to normalize the HSV value and then there is the recognition
 *  */
string FeatureExtractor::getRegionColor(cv::vector<cv::Point> points){
	//extract the bounding box of the shape in a new image
	cv::Rect boundingBox = boundingRect(cv::Mat(points));
	cv::Mat boundedImg = image(boundingBox);

	//convert the image in a binary one
	cv::Mat binary,gray;
	cv::cvtColor(boundedImg, gray, CV_BGR2GRAY);
	int thresholdValue = 128;
	cv::threshold(gray, binary, thresholdValue, 255, CV_THRESH_BINARY);
	//cv::imshow( "bin", binary );
	//cv::waitKey(0);

	//convert the boundedImg in HSV and split it in 3 levels
	cv::Mat hsvRegion;
	cv::cvtColor(boundedImg, hsvRegion, CV_BGR2HSV);
	cv::Mat hsvChannels[3];
	cv::split(hsvRegion, hsvChannels);

	//Use the binary image as a flag foreground - background. The object is black.
	//Compute the average of the object pixels to have the overall color of the object.
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

	//Normalize Opencv values as Gimp values
	double hue = this->normHue(regionH);
	double sat = this->normSV(regionS);
	double val = this->normSV(regionV);

	//printf("%.2f\n",regionH);

	//returns the correct string
	return this->getColorString(hue,sat,val);
}


double FeatureExtractor::normHue(int hueVal){
	//transform the opencv hue value [0,180] to gimp value [0,360]
	return ((double)hueVal*360.0/180.0);
}


double FeatureExtractor::normSV(int svVal){
	//transform the opencv saturation and value values [0,255] to gimp values [0,100]
	return ((double)svVal*100.0/255.0);
}


string FeatureExtractor::getColorString(double gimpHue, double gimpSaturation, double gimpValue){
	//from hue, saturation and value returns a string with the name of the color
	if ((gimpValue >= 0) && (gimpValue <= 30))
		return "black";
	else if (((gimpValue >= 95) && (gimpValue <= 100)) && ((gimpSaturation>=0) && (gimpSaturation<=5)))
		return "white";
	else if (((gimpValue >= 30) && (gimpValue <= 60)) && ((gimpSaturation>=0) && (gimpSaturation<=15)))
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
	//This should never happen
	else return "unknown";
}

void FeatureExtractor::recognizeCircles(){
	cv::Mat gray;
	cv::Mat circleImg = cv::Mat::zeros(image.rows,image.cols,CV_8UC3);

	/// Convert it to gray
	cv::cvtColor( image, gray, CV_BGR2GRAY );


	/// Reduce the noise so we avoid false circle detection
	cv::GaussianBlur( gray, gray, cv::Size(9, 9), 2, 2 );

	cv::vector<cv::Vec3f> circles;

	/// Apply the Hough Transform to find the circles
	cv::HoughCircles( gray, circles, CV_HOUGH_GRADIENT, 1, gray.rows/8, 200, 100, 0, 0 );


	for( size_t i = 0; i < circles.size(); i++ ) {
		cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);

		circleList.push_back(new Circle(radius, center.x,center.y));

		/// Draw the circles detected
		// circle center
		circle( circleImg, center, 3, cv::Scalar(0,255,0), -1, 8, 0 );
		// circle outline
		circle( circleImg, center, radius, cv::Scalar(0,0,255), 3, 8, 0 );
	}

	/// Show your results
#ifndef NO_IMG_SHOW
	cv::namedWindow( "Hough Circle Transform Demo", CV_WINDOW_AUTOSIZE );
	cv::imshow( "Hough Circle Transform Demo", circleImg );

	cv::waitKey(0);
#endif
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
	for (int c = 0; c < 3; c++) {
		int ch[] = {c, 0};
		// extract the single colour level in gray0
		cv::mixChannels(&blurred, 1, &gray0, 1, ch, 1);

		// try several threshold levels (0,1 and 2)
		const int threshold_level = 2;
		for (int l = 0; l < threshold_level; l++) {
			// Use Canny instead of zero threshold level!
			// Canny helps to catch squares with gradient shading
			if (l == 0) {
				Canny(gray0, gray, 10, 20, 3); //

				// Dilate helps to remove potential holes between edge segments
				cv::dilate(gray, gray, cv::Mat(), cv::Point(-1,-1));
			}
			else {
				gray = gray0 >= (l+1) * 255 / threshold_level;
			}

			// Find contours and store them in a list
			cv::findContours(gray, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

			// Test contours
			cv::vector<cv::Point> approx;
			//cout << contours.size();
			for (size_t i = 0; i < contours.size(); i++) {
					// approximate contour with accuracy proportional to the contour perimeter
					cv::approxPolyDP(cv::Mat(contours[i]), approx, arcLength(cv::Mat(contours[i]), true)*0.02, true);

					// Note: absolute value of an area is used because area may be positive or negative - in accordance with the
					// contour orientation
					if (approx.size() == 4 && cv::isContourConvex(cv::Mat(approx))) {
						squares.push_back(approx);
					}
			}
		}
	}

	//draw squares
	cv::Mat rects;
	rects = cv::Mat::zeros(image.rows,image.cols,CV_8UC3);


	//sort clockwise the points of each square
	for ( unsigned int i = 0; i< squares.size(); i++ ) {
		squares.at(i) = sort4PointsClockwise(squares.at(i));
	}


	//delete squares with two points too close one to each other
	squares = deleteFalseSquares(squares);

	//ordino secondo il vettore secondo la coordinata x e poi y del primo punto
	squares = squaresSort(squares);

	//delete overlapped squares
	squares = deleteOverlapped(squares);


	//draw each square with its bounding box on the image
	if (squares.size() > 0) {
		for (unsigned int i = 0; i< squares.size(); i++ ) {
			// draw square
			cv::drawContours(rects, squares, i, cv::Scalar(255,0,0), 1, 8, std::vector<cv::Vec4i>(), 0, cv::Point()); //blue

			// draw bounding rect
			cv::Rect rect = boundingRect(cv::Mat(squares[i]));
			cv::rectangle(rects, rect.tl(), rect.br(), cv::Scalar(0,255,0), 2, 8, 0); //verde

/*
			//prints the coordinates of the square
			printf("F %d: ",i+1);
			for (unsigned int j=0;j<squares.at(i).size();j++){
				printf("(%d,%d)  ",squares.at(i).at(j).x,squares.at(i).at(j).y);
			}
			printf("\n\n");
*/
			//create the quadrilateral
			Quadrilateral *q = new Quadrilateral(squares.at(i).at(0).x,squares.at(i).at(0).y,squares.at(i).at(1).x,squares.at(i).at(1).y,squares.at(i).at(2).x,squares.at(i).at(2).y,squares.at(i).at(3).x,squares.at(i).at(3).y);

			//calculate the color of the quadrilateral
			string color = this->getPointColor(q->getCenter().x,q->getCenter().y);
			//add the color to the quadrilateral
			q->setColor(color);

			//add each square to the quadrilaterl list
			this->quadrilateralList.push_back(q);
		}
	}

#ifndef NO_IMG_SHOW
	cv::imshow("quadr",rects);
	cv::waitKey(0);
#endif
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
			if (l == 0) {
				Canny(gray0, gray, 10, 20, 3); //

				// Dilate helps to remove potential holes between edge segments
				cv::dilate(gray, gray, cv::Mat(), cv::Point(-1,-1));
			}
			else {
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
					if (approx.size() == 3 && cv::isContourConvex(cv::Mat(approx)))  {
						triangles.push_back(approx);
					}
			}
		}
	}

	//draw triangles
	cv::Mat triangleImg;
	triangleImg = cv::Mat::zeros(image.rows,image.cols,CV_8UC3);


	//sort clockwise the points of each triangle
	for ( unsigned int i = 0; i< triangles.size(); i++ ) {
		triangles.at(i) = sort4PointsClockwise(triangles.at(i));
	}


	//delete triangles with two points too close one to each other
	triangles = deleteFalseTriangles(triangles);

	//ordino secondo il vettore secondo la coordinata x e poi y del primo punto
	triangles = squaresSort(triangles);

	//delete overlapped triangles
	triangles = deleteOverlapped(triangles);

	//draw each triangle with its bounding box on the image
	if (triangles.size() > 0) {
		for (unsigned int i = 0; i< triangles.size(); i++ ) {

			// draw contour
			cv::drawContours(triangleImg, triangles, i, cv::Scalar(255,0,0), 1, 8, std::vector<cv::Vec4i>(), 0, cv::Point()); //blue

			// draw bounding rect
			cv::Rect rect = boundingRect(cv::Mat(triangles[i]));
			cv::rectangle(triangleImg, rect.tl(), rect.br(), cv::Scalar(0,255,0), 2, 8, 0); //verde
			/*
			printf("F %d: ",i+1);
			for (unsigned int j=0;j<triangles.at(i).size();j++){
				printf("(%d,%d)  ",triangles.at(i).at(j).x,triangles.at(i).at(j).y);
			}
			printf("\n\n");
			*/
			//add each square to the quadrilaterl list
			this->triangleList.push_back(new Triangle(triangles.at(i).at(0).x,triangles.at(i).at(0).y,triangles.at(i).at(1).x,triangles.at(i).at(1).y,triangles.at(i).at(2).x,triangles.at(i).at(2).y));
		}
	}
#ifndef NO_IMG_SHOW
	cv::imshow("triangles",triangleImg);
	cv::waitKey(0);
#endif
}

/*
 *  One way to tell if an object is an ellipse is to look at the relationship
 *  of its area to its dimensions.  If its actual occupied area can be estimated
 *  using the well-known area formula Area = PI*A*B, then it has a good chance of
 *  being an ellipse.
 * */
void FeatureExtractor::recognizeEllipses(){
	//TODO
	/*
	// We need this to be high enough to get rid of things that are too small too have a definite shape.
	double minArea = 100.00;
	// This value is the maximum permissible error between actual and estimated area.
	double maxTol = 100.00;

	// create the structure that contains the ellipses
	cv::vector<cv::vector<cv::Point> > ellipses;

	// blur will enhance edge detection
	cv::Mat blurred(image);
	cv::medianBlur(image, blurred, 9);

	// create two gray images
	cv::Mat gray0(blurred.size(), CV_8U), gray;
	// create the structure that contains contours
	cv::vector<cv::vector<cv::Point> > contours;

	// find ellipses in every color plane of the image
	for (int c = 0; c < 3; c++)
	{
		int ch[] = {c, 0};
		// extract the single color level in gray0
		cv::mixChannels(&blurred, 1, &gray0, 1, ch, 1);

		// try several threshold levels (0,1 and 2)
		const int threshold_level = 2;
		for (int l = 0; l < threshold_level; l++) {
			// Use Canny instead of zero threshold level!
			// Canny helps to catch squares with gradient shading
			if (l == 0) {
				Canny(gray0, gray, 10, 20, 3); //

				// Dilate helps to remove potential holes between edge segments
				cv::dilate(gray, gray, cv::Mat(), cv::Point(-1,-1));
			}
			else {
				gray = gray0 >= (l+1) * 255 / threshold_level;
			}

			// Find contours and store them in a list
			cv::findContours(gray, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

			// Test contours
			cv::vector<cv::Point> approx;
			for (size_t i = 0; i < contours.size(); i++) {
				//skip if the area is too small
				double actual_area = fabs(cv::contourArea(contours[i], false));
				if (actual_area < minArea)
					continue;

				// FIXME: Assuming the axes of the ellipse are vertical/perpendicular.

				//cv::Rect rect = ((cv::Mat *)contours)->rect;
				cv::Rect rect = boundingRect(cv::Mat(contours[i]));
				int A = rect.width / 2;
				int B = rect.height / 2;
				double estimated_area = M_PI * A * B;
				double error = fabs(actual_area - estimated_area);
				//skip if the difference between the
				if (error > maxTol)
					continue;

				//add the ellipse into the ellipse list
				//ellipses.push_back();
				printf
					(
						 "center x: %d y: %d A: %d B: %d\n",
						 rect.x + A,
						 rect.y + B,
						 A,
						 B
					);
					//if (approx.size() == 3 && cv::isContourConvex(cv::Mat(approx)))  {
					//	triangles.push_back(approx);

			}
		}
	}



//            CvScalar color = CV_RGB( rand() % 255, rand() % 255, rand() % 255 );
//            cvDrawContours( dst, contour, color, color, -1, CV_FILLED, 8, cvPoint(0,0));
        }
*/
}

#ifdef ENRICO
cv::Mat * getCroppedImg(cv::Mat img, Quadrilateral * q){

	Marker * m = dynamic_cast<Marker*>(q);
	int height =0;

	/** If position of the image to crop exceed the border of the image, reduce it */
	if (m->getBbox().y + m->getBbox().height *2 >  img.size().height)
		height = img.size().height-(  m->getBbox().y + m->getBbox().height ) -1;
	else
		height = m->getBbox().height;

	cv::Rect roi(m->getBbox().x, m->getBbox().y + m->getBbox().height , m->getBbox().width , height);
	cv::Mat * croppedImage = new cv::Mat(img(roi).clone());
	//m->setImage(croppedImage);

	return croppedImage;
	//cv::imwrite(path, croppedImage);
}
#endif

std::vector<Object *> FeatureExtractor::getExtractedFeature(){
#ifdef ENRICO

	//Modifica il comportamento: separa le parti che usano ARToolkit da quelle che non lo usano
	if(!findMarkers){
#endif
/*
		//TODO: alla fine eliminare tutto questo schifo ee far ritornare solo la lista di oggetti
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
		//cout<<"color: "+this->getRegionColor(p1)+"\n";	//rosso
 */

		this->recognizeCircles();
		this->recognizeSquares();
		this->recognizeTriangles();
		this->recognizeEllipses();

		//concatenate everything in a vector of objects
		this->objectList.insert(objectList.end(),this->quadrilateralList.begin(),this->quadrilateralList.end());
		this->objectList.insert(objectList.end(),this->triangleList.begin(),this->triangleList.end());
		this->objectList.insert(objectList.end(),this->circleList.begin(),this->circleList.end());

		return objectList;
#ifdef ENRICO
	}
	else {
		quadrilateralList.clear();
		bool allWithQr = true;
		std::vector<Quadrilateral *> newList;
		std::vector<Quadrilateral *> oldList;
		// = new QRScanner("./img.jpg");
		int N_MARKERS = 2;
		int FRAME_TO_PARSE = 10;

#ifdef ALTRO_CODICE
		for(int i= 0; i < FRAME_TO_PARSE; i++){
			initMarkersData();
			newList.clear();
			newList = getMarkers();
			cv::Mat * frame = getFrame();
			allWithQr = true;

			for(int i = 0; i < newList.size();i++){
				Marker * m = dynamic_cast<Marker*>(newList.at(i));

				/** Sets part of the frame as attribute of the Marker */
				m->setImage(getCroppedImg(*frame, m));

				/** Saves part of the frame to disk */
				string path = "temp.jpg";
				cv::imwrite(path, *m->getImage());

				/** Loads saved image and search for a QRCode */
				QRScanner * qrs = new QRScanner(path);

				/** If a QRCode is found creates a QRObjects and sets it as attribute of Marker */
				if(qrs->QRDetected()){
					QRObject * qro;
					qro = new QRObject(qrs->getQRCode());
					m->setQr(qro);
				}
				allWithQr &= qrs->QRDetected();
			}

			if(allWithQr && newList.size()== N_MARKERS)
				return newList;
			else{
				std::vector<Marker *> bestList;
				for(int i = 0; i < newList.size();i++){
						 Marker * newMarker = dynamic_cast<Marker*>(newList.at(i));
						 Marker * oldMarker = NULL;
						 for(int j =0; j<oldList.size(); j++)
							 if( (dynamic_cast<Marker*>(oldList.at(j)))->getId()== newMarker->getId()){
								 oldMarker = dynamic_cast<Marker*>(oldList.at(j));
								 break;
							 }
						 if(oldMarker == NULL)
							 bestList.push_back(newMarker);
						 else if(newMarker->getQRStatus())
							 bestList.push_back(newMarker);
						 else if(oldMarker->getQRStatus())
							 bestList.push_back(oldMarker);
						 else
							 bestList.push_back(newMarker);
						 //TODO manca il caso in cui non c'è nella lista nuova
				}
				oldList.clear();
				std::copy(bestList.begin(), bestList.end(), oldList.begin());
				bool allWithQRcode = true;
				for(int i = 0; i < oldList.size();i++)
					allWithQRcode &= (dynamic_cast<Marker*>(oldList.at(i))->getQRStatus());

				if(oldList.size() == N_MARKERS && allWithQRcode)
					return oldList;
				//oldList = bestList;
			}
		}
		return oldList;
#endif

		initMarkersData();
		quadrilateralList = getMarkers();
		cv::Mat * frame = getFrame();

		cv::imwrite(IMG_PATH, *frame);

		QRScanner * qrs;



		for(int i = 0; i < quadrilateralList.size();i++){
			Marker * m = dynamic_cast<Marker*>(quadrilateralList.at(i));

			/** Sets part of the frame as attribute of the Marker */
			m->setImage(getCroppedImg(*frame, m));

			/** Saves part of the frame to disk */
			string path = "temp.jpg";
			//cv::imwrite(path, *m->getImage());

			/** Loads saved image and search for a QRCode */
			//qrs = new QRScanner(path);
			qrs = new QRScanner(m->getImage());

			/** If a QRCode is found creates a QRObjects and sets it as attribute of Marker */
			if(qrs->QRDetected()){
				QRObject * qro;
				qro = new QRObject(qrs->getQRCode());
				m->setQr(qro);
				cv::Mat * withText = new cv::Mat(m->getImage()->clone());
				cv::putText(*withText, m->getQR()->getContent(), cvPoint(10,20),
				    cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(255,0,0), 1, CV_AA);
				cv::imshow("Decoded QR",*(m->getImage()));
				cv::waitKey();
			}

		}


		//qrs->QRDetected();
		//qrs->getQRCode();

		this->objectList.clear();
		this->objectList.insert(objectList.end(),this->quadrilateralList.begin(),this->quadrilateralList.end());
		return objectList;
	}
#endif
}

//------------------------------------------------------------------------------------------------------------
