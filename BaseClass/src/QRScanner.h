/*
 * QRScanner.h
 *
 *  Created on: 13/nov/2012
 *      Author: enrico
 */
#ifdef ENRICO
#ifndef QRSCANNER_H_
#define QRSCANNER_H_
#include <zbar.h>
using namespace std;

class QRScanner{
public:
	QRScanner(string path);
	~QRScanner();
	string getQRCode();
	bool QRDetected();
private:
	zbar::Image * myImage;
	int numLines;
};

#endif /* QRSCANNER_H_ */
#endif
