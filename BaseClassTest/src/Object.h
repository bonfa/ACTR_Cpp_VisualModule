/*
 * Object.h
 *
 *  Created on: 30/ott/2012
 *      Author: enrico
 *
 *  This object represents everything that can be recognized in an image.
 *
 *	An object can be a geometric shape as well as a qr code.
 */

//TODO make it abstract

#include <iostream>
#include "utils.h"
#include "MyPoint.h"
#include "Rect.h"

using namespace std;


#ifndef OBJECT_H_
#define OBJECT_H_

class Object {
public:
	Object();
	Object(bool attended, double rotation, Rect bbox);
	Object(bool attended, double rotation, int x, int y, int width, int height);
	virtual ~Object();
	/** Returns a string which contains the basic information about the object*/
	virtual string getChunk() =0;
	/** Returns the bounding box of the object*/
	Rect getBbox();
	/** Returns the 'center' of the object*/
	Point getCenter();
	/** Returns the 'rotation' of the object*/
	double getRotation();
protected:
	/** Set the bounding box around the object*/
	void setBbox(int x, int y, int height, int width);
	/** set  the center of the object*/
	void setCenter();
	/** A boolean that is true if the object has already sent to actr ?(//todo: check if it is useful or not)? */
	bool attended;
	/** Gives the rotation in the counter clockwise order
	*
	* * @ATTENTION: as in the images the y axis is positive moving downward
	* and the x axis is positive moving rightward,
	* the rotation is given starting from the horizontal direction in clockwise direction starting
	* 							x
	*  ---------------------------->
	*  |\) rotation
	*  | \
	*  |  \
	*  |   \
	*  |    \
	*  |
	*  |
	*  |
	*  |
	* y|
	*
	* */
	double rotation;
	/** The center of the object. It is defined as the center of the bounding box of the object */
	Point center;
	/** The bounding box of the object. It has rectangular shape */
	Rect bbox;
};



#endif /* OBJECT_H_ */
