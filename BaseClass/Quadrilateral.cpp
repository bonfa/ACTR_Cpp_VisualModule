/*
 * Quadrilateral.cpp
 *
 *  Created on: 30/ott/2012
 *      Author: enrico
 */

#include "Quadrilateral.h"

Quadrilateral::Quadrilateral() {
	// TODO Auto-generated constructor stub

}

Quadrilateral::~Quadrilateral() {
}

Quadrilateral::Quadrilateral(int ax,int ay,int bx,int by,int cx,int cy,int dx,int dy){
	if(ax<0 || ay<0 || bx<0 || by<0 || cx<0 || cy<0 || dx<0 || dy<0)
		printf("Eccezione");//TODO
	if((ax == bx && bx == cx) || (ax == bx && bx == dx) ||(bx == cx && cx == dx) || (ax == cx && cx == dx) ||
			(ay == by && by == cy) || (ay == by && by == dy) ||(by == cy && cy == dy) || (ay == cy && cy == dy))
		printf("Eccezione");//TODO


	a = cvPoint(ax, ay);
	b = cvPoint(bx, by);
	c = cvPoint(cx, cy);
	d = cvPoint(dx, dy);
	std::vector<CvPoint> coords;
	coords.push_back(a);
	coords.push_back(b);
	coords.push_back(c);
	coords.push_back(d);
	Sort4PointsClockwise(coords);
	/*stable_sort(coords.begin(), coords.end(), xComparator);
	stable_sort(coords.begin(), coords.end(), yComparator);*/
	a = coords.at(0);
	b = coords.at(1);
	c = coords.at(2);
	d = coords.at(3);

	area = erone(a, b, c) + erone(a, c , d);
}

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

string Quadrilateral::getChunk(){
	return "cianc, Quadrilateral\n";
}

bool xComparator(CvPoint a, CvPoint b){
	return (a.x < b.x);
}

bool yComparator(CvPoint a, CvPoint b){
	return (a.y < b.y);
}
