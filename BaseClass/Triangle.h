/*
 * Triangle.h
 *
 *  Created on: 30/ott/2012
 *      Author: enrico
 */

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "Blob.h"

class Triangle: public Blob {
public:
	Triangle();
	Triangle(int ax,int ay,int bx,int by,int cx,int cy,int dx,int dy);
	virtual ~Triangle();
	string getChunk();
	double getArea();
private:
	CvPoint a;
	CvPoint b;
	CvPoint c;
};

#endif /* TRIANGLE_H_ */
