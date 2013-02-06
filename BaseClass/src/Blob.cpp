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

Json::Value Blob::getJson(){
	return Object::getJson();
}

string Blob::getChunk(){ //TODO copy from quadrilateral
	return Object::getChunk();
	/*string chunk = "{";
	chunk.append("\"type\": \"Quadrilateral\",");
	chunk.append("\"bbox\": {");
	chunk.append("\"x1\":");
	chunk.append("\"");
	chunk.append(intToString(this->bbox.x));
	chunk.append("\",");
	
	chunk.append("\"y1\":");
	chunk.append("\"");
	chunk.append(intToString(this->bbox.y));
	chunk.append("\",");
	
	chunk.append("\"x2\":");
	chunk.append("\"");
	chunk.append(intToString(this->bbox.x+this->bbox.width));
	chunk.append("\",");
	
	chunk.append("\"y2\":");
	chunk.append("\"");
	chunk.append(intToString(this->bbox.y+this->bbox.height));
	chunk.append("\"");
	chunk.append("}");
	chunk.append(",");
	chunk.append("\"color\": ");
	chunk.append("\"");
	chunk.append(this->color);
	chunk.append("\"");
	chunk.append("}");
	return chunk;*/
}

double Blob::getArea(){
	if(area <= 0)
		cout << ("Eccezione"); //TODO
	return area;
}



