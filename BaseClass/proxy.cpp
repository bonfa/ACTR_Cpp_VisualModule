/*
 *  proxy.cpp
 *  library
 *
 *  Created by Stefano Bennati on 11/9/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "proxy.h"

void Proxy::demo() {
	FeatureGetter *ba = new FeatureGetter();

	cv::imshow("finestra",ba->getImage("./lena.jpg"));
	cv::waitKey(0);

	cv::VideoCapture cap = ba->getStream();
	ba->showVideo(cap);
	
	cv::destroyAllWindows();
	delete ba;
}

int Proxy::test() {

	return 10;
}

double Proxy::area(){
	Triangle * tri = new Triangle(0,0,2,0,0,2);
	return tri->getArea();
}
