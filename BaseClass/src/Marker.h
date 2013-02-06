/*
 * Marker.h
 *
 *  Created on: 30/ott/2012
 *      Author: enrico
 *
 *  This class represent a button.
 *  A button is a rectangle with some text inside.
 *
 *  It is defined by a point, which is the starting point of the rectangle
 *  and the width and the height of the rectangle itself.
 *  In a common 2D space, the point is the bottom-left point of the rectangle.
 *  In a 2D space as the one defined by the opencv Mat it is the top left point of the rectangle.
 *  @ATTENTION: the coordinates must not be negative
 */
#include "author.h"
#ifdef ENRICO

#ifndef MARKER_H_
#define MARKER_H_

#include "Quadrilateral.h"
#include "QRObject.h"
#include <sstream>
#include <string>
#include <cv.hpp>
#include <cxcore.hpp>
#include <cv.h>
#include <highgui.h>

class Marker: public Quadrilateral {
public:
	Marker();
	~Marker();
	Marker(int ax,int ay,int bx,int by,int cx,int cy,int dx,int dy, int id_, double _attitudeAngle);
	/** Returns a string which contains the basic information about the button*/
	string getChunk();
	
	void setQr(QRObject *qr_){
		qr = qr_;
		QRStatus = true;
	};
	
	QRObject* getQR(){return qr;};
	int getId(){return id;};
	bool getQRStatus(){return QRStatus;};
	void setImage(cv::Mat * _image){image = _image;};
	cv::Mat * getImage(){return image;};
	
protected:
	/** Creates a Json object that contains the basic information about the quadrilateral*/
	virtual Json::Value getJson();
private:
	double attitudeAngle;
	cv::Mat * image;
	QRObject *qr;
	int id;
	bool QRStatus; 
};

#endif /* MARKER_H_*/
#endif /* ENRICO */
