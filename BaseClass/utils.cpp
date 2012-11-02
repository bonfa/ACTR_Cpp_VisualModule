/*
 * utils.cpp
 *
 *  Created on: 02/nov/2012
 *      Author: enrico
 */
#include "utils.h"



void Sort4PointsClockwise(std::vector<CvPoint> points){
	CvPoint& a = points[0];
	CvPoint& b = points[1];
	CvPoint& c = points[2];
	CvPoint& d = points[3];

	double abc = a.x * b.y - a.y * b.x + b.x * c.y - b.y * c.x + c.x * a.y - c.y * a.x;
	if(abc < 0.0){
		double acd = a.x * c.y - a.y * c.x + c.x * d.y - c.y * d.x + d.x * a.y - d.y * a.x;
		if(acd < 0.0){
    		return;
    	}
    	else {
    		double abd = a.x * b.y - a.y * b.x + b.x * d.y - b.y * d.x + d.x * a.y - d.y * a.x;
    		if(abd < 0){
    			std::swap(d, c);
    		}
    		else{
    			std::swap(a, d);
    		}
    	}
    }
    else {
    	double acd = a.x * c.y - a.y * c.x + c.x * d.y - c.y * d.x + d.x * a.y - d.y * a.x;
    	if(acd < 0.0){
    		double abd = a.x * b.y - a.y * b.x + b.x * d.y - b.y * d.x + d.x * a.y - d.y * a.x;
    		if(abd < 0.0){
    			std::swap(b, c);
    		}
    		else{
    			std::swap(a, b);
    		}
    	}
    	else {
    		std::swap(a, c);
    	}
    }
}


int getMinMax(const std::vector<CvPoint>& coords, int type) {
	int out;
	int i;
	for (i = 0; i < coords.size(); i++) {
		if (type == MAX_X && coords[i].x > out)
			out = coords[i].x;
		else if(type == MAX_Y && coords[i].y > out)
			out = coords[i].y;
		else if(type == MIN_X && coords[i].x < out)
			out = coords[i];
		else if(type == MIN_Y && coords[i].y < out)
			out = coords[i];
	}
	return out;
}

