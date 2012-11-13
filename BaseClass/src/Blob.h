/*
 * Blob.h
 *
 *  Created on: 30/ott/2012
 *      Author: enrico
 */



#ifndef BLOB_H_
#define BLOB_H_

#include <iostream>
#include "Object.h"

class Blob: public Object {
public:
	Blob();
	virtual ~Blob();
	virtual string getChunk() =0;
	double getArea();
protected:
	double area;
private:
	//TODO: colore
};

#endif /* BLOB_H_ */
