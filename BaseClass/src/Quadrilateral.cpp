/*
 * Quadrilateral.cpp
 *
 *  Created on: 30/ott/2012
 *      Author: enrico
 */

#include "Quadrilateral.h"


Quadrilateral::Quadrilateral() {
	// TODO Auto-generated constructor stub
	//TODo cancellare
}

Quadrilateral::~Quadrilateral() {
}

/**
 * Constructor
 * 1) check that all the coordinates are not negative
 * 2) check that the points are not on the same line
 * 3) sort the vertices following the clockwise order
 * 4) creates the quadrilateral
 * 5) set the area
 * 6) set the bounding box
 * 7) set the center of the bounding box
 * */
Quadrilateral::Quadrilateral(int ax,int ay,int bx,int by,int cx,int cy,int dx,int dy, string color){
	//TODO sistemare questo controllo!!!
	if(ax<0 || ay<0 || bx<0 || by<0 || cx<0 || cy<0 || dx<0 || dy<0)
		throw InputException("Negative coordinate");

	if (inLinePoints(ax,ay,bx,by,cx,cy) || inLinePoints(ax,ay,bx,by,dx,dy) || inLinePoints(dx,dy,bx,by,cx,cy) ||inLinePoints(ax,ay,cx,cy,dx,dy))
		throw InputException("More than two points on the same line");

	int maxX, minX, maxY, minY;

	a = Point(ax, ay);
	b = Point(bx, by);
	c = Point(cx, cy);
	d = Point(dx, dy);

	std::vector<Point> coords;
	coords.push_back(a);
	coords.push_back(b);
	coords.push_back(c);
	coords.push_back(d);

	Sort4PointsClockwise(coords);

	a = coords.at(0);
	b = coords.at(1);
	c = coords.at(2);
	d = coords.at(3);

	area = erone(a, b, c) + erone(a, c , d);

	maxX = getMinMax(coords, MAX_X);
	maxY = getMinMax(coords, MAX_Y);
	minX = getMinMax(coords, MIN_X);
	minY = getMinMax(coords, MIN_Y);

	setBbox(minX, minY, maxY - minY, maxX-minX);
	this->setCenter();
	this->setRotation();
	this->setColor(color);
}


Point Quadrilateral::getA(){
	return this->a;
}



Point Quadrilateral::getB(){
	return this->b;
}



Point Quadrilateral::getC(){
	return this->c;
}


Point Quadrilateral::getD(){
	return this->d;
}

void Quadrilateral::setA(Point* p){
	this->a.x = p->x;
	this->a.y = p->y;
}

void Quadrilateral::setB(Point* p){
	this->b.x = p->x;
	this->b.y = p->y;
}

void Quadrilateral::setC(Point* p){
	this->c.x = p->x;
	this->c.y = p->y;
}

void Quadrilateral::setD(Point* p){
	this->d.x = p->x;
	this->d.y = p->y;
}




/**
 * @ATTENTION: @see Object.h for a better explanation of the 'rotation' parameter
 *
 * @ATTENTION: tested by the test 'checkRotation'
 */
void Quadrilateral::setRotation(){
	//Get the equations of the edges
	std::vector<Segment> edgeList = this->getEdgesLine();

	//Create a list which contains the artg(m) of every non vertical line (all the values are >= 0)
	std::vector<double> rotationList;
	for (unsigned int i=0; i<edgeList.size(); i++){

		//If the line is vertical insert directly PI/2
		if (((edgeList.at(i)).isVertical()))
			rotationList.push_back(M_PI/2);
		//Else, calculate the angle
		else {
			double atg = atan2((edgeList.at(i)).getSlope(),1);
			//when the angle is < 0, add PI to make it positive (this does not change the m)
			if (atg < 0)
				atg += M_PI;
			rotationList.push_back(atg);
		}
	}
	rotation = getMin(rotationList);
}


std::vector<Segment> Quadrilateral::getEdgesLine(){
	std::vector<Segment> lineList;

	Segment line1 = Segment(a,b);
	Segment line2 = Segment(b,c);
	Segment line3 = Segment(c,d);
	Segment line4 = Segment(d,a);

	lineList.push_back(line1);
	lineList.push_back(line2);
	lineList.push_back(line3);
	lineList.push_back(line4);

	return lineList;
}

Json::Value Quadrilateral::getJson(){
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
	Json::Value p4;
	p4["x"] = this->d.x;
	p4["y"] = this->d.y;
	//creating the vertices' array
	Json::Value vertices(Json::arrayValue);
	vertices.append(p1);
	vertices.append(p2);
	vertices.append(p3);
	vertices.append(p4);
	//put all together in the hierarchy
	obj["Bbox"]=Object::getJson();
	obj["Vertices"]=vertices;
	obj["Type"]="Quadrilateral";
	obj["Color"]=this->color;
	return obj;
}


string Quadrilateral::getChunk(){
	Json::FastWriter writer;
	std::string s = writer.write(this->getJson());
	if (!s.empty() && s[s.length()-1] == '\n') {
		s.erase(s.length()-1);
	}
	//cout << s + "\n";
	return s;
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
	return 	chunk;*/
}
















