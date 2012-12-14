/*
 * Blob.h
 *
 *  Created on: 30/ott/2012
 *      Author: enrico
 *
 *  This class represents a generic geometrical shape recognized in an image.
 *  Shapes of this kind are rectangles, circles, triangles, ecc...
 *  It inherits from the Object class.
 */



#ifndef BLOB_H_
#define BLOB_H_

#include <iostream>
#include "Object.h"

class Blob: public Object {
public:
	Blob();
	virtual ~Blob();
	/** Return a string which contains the basic information about the shape*/
	virtual string getChunk() =0;
	/** Return the area of the shape */
	double getArea();
protected:
	/** The area of the object */
	double area;
private:
	//TODO: colore
};

#endif /* BLOB_H_ */
