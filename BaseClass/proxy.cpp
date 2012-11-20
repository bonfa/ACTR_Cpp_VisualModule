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
	BaseClass *ba = new BaseClass();

	imshow("finestra",ba->getImage("./lena.jpg"));
	waitKey(0);

	VideoCapture cap = ba->getStream();
	ba->showVideo(cap);
	
	cv::destroyAllWindows();
	delete ba;
}

int Proxy::test() {

	return 10;
}