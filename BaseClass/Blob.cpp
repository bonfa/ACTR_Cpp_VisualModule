/*
 * Blob.cpp
 *
 *  Created on: 30/ott/2012
 *      Author: enrico
 */

#include "Blob.h"

Blob::Blob() :area(0) {
	//TODO verificare se non da area zero
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

double Blob::getArea(){
	if(area <= 0)
		printf("Eccezione"); //TODO
	return area;
}
