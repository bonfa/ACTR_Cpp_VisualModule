/*
 * Blob.cpp
 *
 *  Created on: 30/ott/2012
 *      Author: enrico
 */

#include "Blob.h"

Blob::Blob() {
	// TODO Auto-generated constructor stub

}

Blob::~Blob() {
	// TODO Auto-generated destructor stub
}

string Blob::getChunk(){
	return "cianc\n";
}

double Blob::erone(CvPoint a, CvPoint b, CvPoint c){
	double ab;
	double bc;
	double ac;
	double p;
	ab = sqrt(((a.x-b.x)^2)+ ((a.y - b.y)^2));
	bc = sqrt(((c.x-b.x)^2)+ ((c.y - b.y)^2));
	ac = sqrt(((a.x-c.x)^2)+ ((a.y - c.y)^2));
	p = (ab + ac + bc)/2;
	return sqrt(p*(p-ab)*(p-bc)*(p-ac));
}
