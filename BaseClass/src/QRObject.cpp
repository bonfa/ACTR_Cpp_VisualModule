/*
 * QRObject.cpp
 *
 *  Created on: 30/ott/2012
 *      Author: enrico
 */

#include "QRObject.h"

QRObject::QRObject(bool detected_, std::string content_) {
	detected = detected_;
	content = content_;
	if(content.compare("") == 0)
		decoded = false;
	else
		decoded = true;
	//TODO verificare se non da area zero
}

QRObject::~QRObject() {
	// TODO Auto-generated destructor stub
}

//TODO: escaping stringhe
string QRObject::getChunk(){
	string chunk = "{";
		chunk.append("\"object\"");
		chunk.append(":");
			chunk.append("{");
			
			chunk.append("\"type\": \"QRCode\",");
			chunk.append("\"detected\": ");
			chunk.append("\"");
			chunk.append(this->detected);
			chunk.append("\"");
			
			chunk.append(",");
			
			chunk.append("\"decoded\": ");
			chunk.append("\"");
			chunk.append(this->decoded);
			chunk.append("\"");
		
			chunk.append(",");
			
			chunk.append("\"content\": ");
			chunk.append("\"");
			chunk.append(this->content);
			chunk.append("\"");
		
		chunk.append("}");
	chunk.append("}");
	return chunk;
}

bool QRObject::isDetected(){
	return detected;
	}
	
bool QRObject::isDecoded(){
	return decoded;
	}
	
string QRObject::getContent(){
	return content;
	}



