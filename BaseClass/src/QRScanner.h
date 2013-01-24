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
#include <opencv2/imgproc/imgproc.hpp>

#include <boost/filesystem.hpp>

using namespace std;

class QRScanner{
public:
	QRScanner(cv::Mat * img);
	QRScanner(std::string path);
	void init(char *raw, int width,int height);
	~QRScanner();
	string getQRCode();
	bool QRDetected();
private:
	zbar::Image * myImage;
	int numLines;
};

#endif /* QRSCANNER_H_ */
#endif
