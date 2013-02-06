/*
 * QRObject.cpp
 *
 *  Created on: 30/ott/2012
 *      Author: enrico
 */

#include "QRObject.h"

QRObject::QRObject(std::string content_) {
	content = content_;
}

QRObject::~QRObject() {
	// TODO Auto-generated destructor stub
}


Json::Value QRObject::getJson(){
	Json::Value obj;// = Object::getJson();
	obj["content"]=this->content;
	return obj;
	
}

string QRObject::getChunk(){
	Json::FastWriter writer;
	return writer.write(this->getJson());
	/*string chunk = "{";
		chunk.append("\"object\"");
		chunk.append(":");
			chunk.append("{");
			
			chunk.append("\"type\": \"QRCode\"");
		
			chunk.append(",");
			
			chunk.append("\"content\": ");
			chunk.append("\"");
			chunk.append(this->content);
			chunk.append("\"");
		
		chunk.append("}");
	chunk.append("}");
	return chunk;*/
}

	
string QRObject::getContent(){
	return content;
	}



