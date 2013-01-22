/*
 * QRObject.h
 *
 *  Created on: 30/ott/2012
 *      Author: enrico
 *
 *  This class represents a generic geometrical shape recognized in an image.
 *  Shapes of this kind are rectangles, circles, triangles, ecc...
 *  It inherits from the Object class.
 */



#ifndef QRObject_H_
#define QRObject_H_

#include <iostream>
#include "Object.h"
#include <string>

class QRObject: public Object {
public:
	QRObject(bool detected_, std::string content_);
	virtual ~QRObject();
	/** Return a string which contains the basic information about the shape*/
	string getChunk();
	bool isDetected();
	bool isDecoded();
	std::string getContent();
private:
	bool detected;
	bool decoded;
	string content;
	//TODO: colore
};

#endif /* QRObject_H_ */
