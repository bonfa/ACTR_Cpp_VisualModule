/*
 * FeatureExtractor.cpp
 *
 *  Created on: 04/dic/2012
 *      Author: francesco
 */

#include "FeatureExtractor.h"
#define MRG 25

FeatureExtractor::FeatureExtractor() {
	// TODO Auto-generated constructor stub

}

FeatureExtractor::~FeatureExtractor() {
	// TODO Auto-generated destructor stub
}

Point3_<uchar>* FeatureExtractor::getPixel(int x, int y, Mat image){
	return image.ptr<Point3_<uchar> >(y,x); //Point3_<uchar>* p
}


string FeatureExtractor::getColor(int x, int y, Mat image){

	Point3_<uchar>* p;
	p = getPixel(x, y, image);

	if(p->z > 250 - MRG && p->y < MRG && p->x < MRG)
		return "red";
	else if(p->z < MRG && p->y < 167 + MRG && p->y > 167 - MRG && p->x > 230 - MRG)
		return "cyan";
	else if(p->z > 250 - MRG && p->y < 219 + MRG && p->y > 219 - MRG && p->x < MRG)
		return "yellow";
	else if(p->z < MRG && p->y < 103 + MRG && p->y > 103 - MRG && p->x < 169 + MRG && p->x > 169 - MRG)
		return "blue";
	else if(p->z > 255 - MRG && p->y < 153 + MRG && p->y > 153 - MRG && p->x < 51 + MRG && p->x > 51 - MRG)
		return "orange";
	else if(p->z > 34 - MRG && p->z < 34 + MRG && p->y < 232 + MRG && p->y > 232 - MRG && p->x < 62 + MRG && p->x > 62 - MRG)
		return "green";
	else if(p->z < 50 && p->y < 50 && p->x < 50 && p->z + p->y + p->x < 120)
		return "black";
	/*
	p->x //B
	p->y //G
	p->z //R */
	return "unknown";
}
