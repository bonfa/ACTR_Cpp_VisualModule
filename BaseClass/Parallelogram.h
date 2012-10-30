/*
 * Parallelogram.h
 *
 *  Created on: 30/ott/2012
 *      Author: enrico
 */

#ifndef PARALLELOGRAM_H_
#define PARALLELOGRAM_H_

#include <cmath>
#include "Blob.h"

class Parallelogram: public Blob {
public:
	Parallelogram();
	Parallelogram(int ax,int ay,int bx,int by,int cx,int cy,int dx,int dy);
	virtual ~Parallelogram();
	string getChunk();
	double getArea();
protected:
	CvPoint a;
	CvPoint b;
	CvPoint c;
	CvPoint d;
};

#endif /* PARALLELOGRAM_H_ */
