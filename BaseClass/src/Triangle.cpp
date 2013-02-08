/*
 * Triangle.cpp
 *
 *  Created on: 30/ott/2012
 *      Author: enrico
 */

#include "Triangle.h"

/**
 * Constructor
 * 1) check that all the coordinates are not negative
 * 2) check that the points are not on the same line
 * 3) creates the triangle
 * 4) set the area
 * 5) set the bounding box
 * 6) set the center of the bounding box
 * */
Triangle::Triangle(int ax,int ay,int bx,int by,int cx,int cy,string color){
	if(ax<0 || ay<0 || bx<0 || by<0 || cx<0 || cy<0)
		throw InputException(("Negative values in the points coordinates"));

	if((ax == bx && bx == cx) || (ay == by && by == cy))
		throw InputException("More than two points on the same line");

	if (inLinePoints(ax,ay,bx,by,cx,cy))
		throw InputException("More than two points on the same line");

	this->a = Point(ax, ay);
	this->b = Point(bx, by);
	this->c = Point(cx, cy);
	this->area = erone(this->a, this->b, this->c);
	this->setBoundingBox();
	this->setCenter();
	this->setRotation();
	this->setColor(color);
}


void Triangle::setBoundingBox() {
	int maxX, minX, maxY, minY;
	std::vector<Point> coords;
	coords.push_back(a);
	coords.push_back(b);
	coords.push_back(c);
	maxX = getMinMax(coords, MAX_X);
	maxY = getMinMax(coords, MAX_Y);
	minX = getMinMax(coords, MIN_X);
	minY = getMinMax(coords, MIN_Y);
	setBbox(minX, minY, maxY - minY, maxX - minX);
}

Json::Value Triangle::getJson(){
	Json::Value obj;
	//creating the vertices
	Json::Value p1;
	p1["x"] = this->a.x;
	p1["y"] = this->a.y;
	Json::Value p2;
	p2["x"] = this->b.x;
	p2["y"] = this->b.y;
	Json::Value p3;
	p3["x"] = this->c.x;
	p3["y"] = this->c.y;
	//creating the vertices' array
	Json::Value vertices(Json::arrayValue);
	vertices.append(p1);
	vertices.append(p2);
	vertices.append(p3);
	//put all together in the hierarchy
	obj["Bbox"]=Object::getJson();
	obj["Vertices"]=vertices;
	obj["Type"]="Triangle";
	obj["Color"]=this->color;
	return obj;
}

string Triangle::getChunk(){
	Json::FastWriter writer;
	return writer.write(this->getJson());
	
	/*string chunk = "{";
	chunk.append("\"type\": \"Triangle\",");
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
	return 	chunk;*/
}


Point Triangle::getA(){
	return this->a;
}



Point Triangle::getB(){
	return this->b;
}



Point Triangle::getC(){
	return this->c;
}




/**
 * @ATTENTION: @see Object.h for a better explanation of the 'rotation' parameter
 */
void Triangle::setRotation(){
	//TODO --> testing
	//TODO --> as this method is the same as the 'Quadrilateral' one, extract it somewhere else to avoid the copy
	//Get the equations of the edges
	std::vector<Segment> edgeList = this->getEdgesLine();

	//Create a list which contains the artg(m) of every non vertical line
	std::vector<double> rotationList;
	for (unsigned int i=0; i<edgeList.size(); i++){
		//exclude the vertical lines (which have the maximum slope)
		if (!((edgeList.at(i)).isVertical())){
			double atg = atan2((edgeList.at(i)).getSlope(),1);
			//when the angle is < 0, add PI to make it positive
			if (atg < 0)
				atg += M_PI;
			rotationList.push_back(atg);
		}
	}
	rotation = getMin(rotationList);
}



std::vector<Segment> Triangle::getEdgesLine(){
	//TODO --> testing
	std::vector<Segment> lineList;

	Segment line1 = Segment(a,b);
	Segment line2 = Segment(b,c);
	Segment line3 = Segment(c,a);

	lineList.push_back(line1);
	lineList.push_back(line2);
	lineList.push_back(line3);

	return lineList;
}



Triangle::~Triangle() {

}


