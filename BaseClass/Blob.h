/*
 * Blob.h
 *
 *  Created on: 30/ott/2012
 *      Author: enrico
 */

#include <opencv/cv.h>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include <opencv/cxcore.h>
#include <iostream>

#ifndef BLOB_H_
#define BLOB_H_

#include "Object.h"

class Blob: public Object {
public:
	Blob();
	virtual ~Blob();
	virtual string getChunk() =0;
	virtual double getArea() =0;
	double erone(CvPoint a, CvPoint b, CvPoint c);
protected:
	int area;
private:
	//TODO: colore
};

#endif /* BLOB_H_ */
