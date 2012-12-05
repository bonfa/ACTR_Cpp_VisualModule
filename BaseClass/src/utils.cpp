/*
 * utils.cpp
 *
 *  Created on: 02/nov/2012
 *      Author: enrico
 */
#include "utils.h"



vector<Point> Sort4PointsClockwise(std::vector<Point> points){
	Point& a = points[0];
	Point& b = points[1];
	Point& c = points[2];
	Point& d = points[3];

	double abc = a.x * b.y - a.y * b.x + b.x * c.y - b.y * c.x + c.x * a.y - c.y * a.x;
	if(abc < 0.0){
		double acd = a.x * c.y - a.y * c.x + c.x * d.y - c.y * d.x + d.x * a.y - d.y * a.x;
		if(acd < 0.0){
    		return points;
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
	std::vector<Point> out;
	out.push_back(a);
	out.push_back(b);
	out.push_back(c);
	out.push_back(d);
	return out;
}


int getMinMax(const std::vector<Point>& coords, int type) {
	int out;
	unsigned int i;

	if(type == MAX_X || type == MIN_X)
		out = coords[0].x;
	else
		out = coords[0].y;

	for (i = 0; i < coords.size(); i++) {
		if 		(type == MAX_X && coords[i].x > out)
			out = coords[i].x;
		else if	(type == MAX_Y && coords[i].y > out)
			out = coords[i].y;
		else if	(type == MIN_X && coords[i].x < out)
			out = coords[i].x;
		else if	(type == MIN_Y && coords[i].y < out)
			out = coords[i].y;
	}
	return out;
}


bool inLinePoints(int ax, int ay, int bx, int by, int cx, int cy ){

	StraightLine *line = new StraightLine(ax,ay,bx,by);
	return line->doesPointBelongTo(cx,cy);
}


double erone(Point a, Point b, Point c){
	double ab;
	double bc;
	double ac;
	double p;
	ab = sqrt((a.x-b.x)*(a.x-b.x)+ (a.y - b.y)*(a.y - b.y));
	bc = sqrt((c.x-b.x)*(c.x-b.x)+ (c.y - b.y)*(c.y - b.y));
	ac = sqrt((a.x-c.x)*(a.x-c.x)+ (a.y - c.y)*(a.y - c.y));
	p = (ab + ac + bc)/2;
	return sqrt(p*(p-ab)*(p-bc)*(p-ac));
}





cv::vector<cv::Point> Sort4cvPointsClockwise(cv::vector<cv::Point> points){
	cv::Point& a = points[0];
	cv::Point& b = points[1];
	cv::Point& c = points[2];
	cv::Point& d = points[3];

	double abc = a.x * b.y - a.y * b.x + b.x * c.y - b.y * c.x + c.x * a.y - c.y * a.x;
	if(abc < 0.0){
		double acd = a.x * c.y - a.y * c.x + c.x * d.y - c.y * d.x + d.x * a.y - d.y * a.x;
		if(acd < 0.0){
    		return points;
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
	cv::vector<cv::Point> out;
	out.push_back(a);
	out.push_back(b);
	out.push_back(c);
	out.push_back(d);
	return out;
}
