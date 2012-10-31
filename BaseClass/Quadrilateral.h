/*
 * Quadrilateral.h
 *
 *  Created on: 30/ott/2012
 *      Author: enrico
 */

#ifndef Quadrilateral_H_
#define Quadrilateral_H_

#include <vector>
#include <cmath>
#include "Blob.h"
#include <algorithm>

	bool xComparator(CvPoint a, CvPoint b);
	bool yComparator(CvPoint a, CvPoint b);
	void Sort4PointsClockwise(std::vector<CvPoint> points);

class Quadrilateral: public Blob {
public:
	Quadrilateral();
	Quadrilateral(int ax,int ay,int bx,int by,int cx,int cy,int dx,int dy);
	virtual ~Quadrilateral();
	string getChunk();

protected:
	CvPoint a;
	CvPoint b;
	CvPoint c;
	CvPoint d;


};

#endif /* Quadrilateral_H_ */
