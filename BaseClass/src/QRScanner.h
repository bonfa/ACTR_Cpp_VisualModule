/*
 * QRScanner.h
 *
 *  Created on: 13/nov/2012
 *      Author: enrico
 */
#include "author.h"
#ifdef ENRICO
#ifndef QRSCANNER_H_
#define QRSCANNER_H_

#include <iostream>
#include <Magick++.h>
#include <zbar.h>

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv/cxcore.h>
#include <string>

#include <boost/filesystem.hpp>

using namespace std;
using namespace zbar;
using namespace cv;
//using namespace std;

class QRScanner{
public:
	QRScanner(std::string path);
	~QRScanner();
	string getQRCode();
	bool QRDetected();
private:
	zbar::Image * myImage;
	int numLines;
};

#endif /* QRSCANNER_H_ */
#endif
