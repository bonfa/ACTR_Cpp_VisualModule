/*
 * Object.h
 *
 *  Created on: 30/ott/2012
 *      Author: enrico
 */

/*
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
*/
#include <iostream>
#include "BaseClassException.h"
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
	virtual string getChunk() =0;
	Rect getBbox();
protected:
	void setBbox(int x, int y, int height, int width);
	bool attended;
	double rotation;
	Rect bbox;
};



#endif /* OBJECT_H_ */
