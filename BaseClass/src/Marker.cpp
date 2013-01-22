/*
 * Marker.cpp
 *
 *  Created on: 30/ott/2012
 *      Author: enrico
 */

#include "Marker.h"


Marker::~Marker() {

}

/**
 * Constructor
 * 1) check that the coordinates of the point are not negative
 * 2) check that the width and the height are positive
 * 3) check that the string is not empty
 * 4) creates the button
 * 5) set the bounding box
 * 6) set the center of the bounding box
 * */
Marker::Marker(int ax,int ay,int bx,int by,int cx,int cy,int dx,int dy, int id_) :Quadrilateral(ax,ay,bx,by,cx,cy,dx,dy){
	id = id_;
	QRStatus = false;
	
}


string Marker::getChunk(){
	return "cianc, bottone\n";
}
