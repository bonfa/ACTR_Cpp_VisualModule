/*
 * Marker.cpp
 *
 *  Created on: 30/ott/2012
 *      Author: enrico
 */


#include "author.h"
#ifdef ENRICO

#include "Marker.h"


Marker::~Marker() {

}

/** //TODO correct?
 * Constructor
 * 1) check that the coordinates of the point are not negative
 * 2) check that the width and the height are positive
 * 3) check that the string is not empty
 * 4) creates the button
 * 5) set the bounding box
 * 6) set the center of the bounding box
 * */
Marker::Marker(int ax,int ay,int bx,int by,int cx,int cy,int dx,int dy, int id_, double _attitudeAngle) :Quadrilateral(ax,ay,bx,by,cx,cy,dx,dy, "Black"){
	id = id_;
	QRStatus = false;
	attitudeAngle = _attitudeAngle;
	//image = NULL;
	//qr = NULL;
}


Json::Value Marker::getJson(){
	Json::Value obj;
	obj["Qrstatus"]= this->QRStatus;
	obj["Id"]= this->id;
	
	std::ostringstream attitudeTemp;
	attitudeTemp << attitudeAngle;
	std::string attitudeStr = attitudeTemp.str();
	
	obj["Attitudeangle"]= attitudeStr;
	obj["Type"]="Marker";
	obj["Quadrilateral"] = Quadrilateral::getJson();
	if(this->QRStatus)
		obj["Qrcode"]= qr->getPJson();
	return obj;
}

string Marker::getChunk(){
	Json::FastWriter writer;
	std::string s = writer.write(this->getJson());
	if (!s.empty() && s[s.length()-1] == '\n') {
		s.erase(s.length()-1);
	}
	return s;
	
	/*stringstream buffer;
	buffer << this->id;

	std::ostringstream strs;
	strs << attitudeAngle;
	std::string attitudeStr = strs.str();

	string chunk = "{";
			chunk.append("\"object\"");
			chunk.append(":");

				chunk.append(Quadrilateral::getChunk());

			chunk.append(",");

				chunk.append("\"qrStatus\": ");
				chunk.append("\"");
				chunk.append( this->QRStatus ? "true" : "false");
				chunk.append("\"");

			chunk.append(",");

				chunk.append("\"id\": ");
				chunk.append("\"");
				chunk.append( buffer.str());
				chunk.append("\"");

			chunk.append(",\"type\": \"Marker\"");

			chunk.append(",\"attitudeAngle\": \"");
			chunk.append(attitudeStr);
			chunk.append("\"");

			if(this->QRStatus){
				chunk.append(",\"qrCode\": ");
				chunk.append(qr->getChunk());
			}

		chunk.append("}");
		return chunk;*/
}

#endif //ENRICO
