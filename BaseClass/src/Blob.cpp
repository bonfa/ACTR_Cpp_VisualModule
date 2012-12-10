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

double Blob::getArea(){
	if(area <= 0)
		cout << ("Eccezione"); //TODO
	return area;
}



