/*
 * Quadrilateral.h
 *
 *  Created on: 30/ott/2012
 *      Author: enrico
 *
 *	This class represent the quadrilateral geometric shape.
 *  It is defined by its 4 vertices.
 *  @ATTENTION: the coordinates must not be negative
 */

#ifndef Quadrilateral_H_
#define Quadrilateral_H_

#include <vector>
#include "Blob.h"
#include "utils.h"
#include "MyPoint.h"




class Quadrilateral: public Blob {
public:
	Quadrilateral();
	Quadrilateral(int ax,int ay,int bx,int by,int cx,int cy,int dx,int dy);
	virtual ~Quadrilateral();
	/** Returns a string which contains the basic information about the quadrilateral*/
	string getChunk();
	/** Returns the first vertex of the quadrilateral*/
	Point getA();
	/** Returns the second vertex of the quadrilateral*/
	Point getB();
	/** Returns the third vertex of the quadrilateral*/
	Point getC();
	/** Returns the fourth vertex of the quadrilateral*/
	Point getD();
protected:
	/** The first vertex*/
	Point a;
	/** The second vertex*/
	Point b;
	/** The third vertex*/
	Point c;
	/** The fourth vertex*/
	Point d;

};

#endif /* Quadrilateral_H_ */
