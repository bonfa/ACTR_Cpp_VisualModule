#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "utilsTest.h"
#include <opencv/cv.h>
#include <vector>
#include <cmath>

void utilsTest01(){
	Point a = Point(1, 1);
	Point b = Point(-1, -1);
	Point d = Point(-1, 1);
	Point c = Point(1, -1);

	std::vector<Point> coords;
	coords.push_back(a);
	coords.push_back(b);
	coords.push_back(c);
	coords.push_back(d);
	std::vector<Point> sorted = Sort4PointsClockwise(coords);

	std::stringstream out;

	out << sorted[0].x << sorted[0].y ;
	out << sorted[1].x << sorted[1].y ;
	out << sorted[2].x << sorted[2].y ;
	out << sorted[3].x << sorted[3].y ;
	ASSERT_EQUAL("111-1-1-1-11",out.str());
}

void utilsTest02(){
	Point a = Point(10, 22);
	Point b = Point(-12, 11);
	Point d = Point(-1, -6);
	Point c = Point(0, -4);

	std::vector<Point> coords;
	coords.push_back(a);
	coords.push_back(b);
	coords.push_back(c);
	coords.push_back(d);

	ASSERT_EQUAL(10,getMinMax(coords, MAX_X));
	ASSERT_EQUAL(22,getMinMax(coords, MAX_Y));
	ASSERT_EQUAL(-12,getMinMax(coords, MIN_X));
	ASSERT_EQUAL(-6,getMinMax(coords, MIN_Y));
}

void utilsTest04(){
	Point a = Point(0, 0);
	Point b = Point(1,0);
	Point c = Point(0, 2);

	ASSERT_EQUAL(1,erone(a,b,c));
	ASSERT_EQUAL(1,erone(b,a,c));
	ASSERT_EQUAL(1,erone(c,a,b));
	ASSERT_EQUAL(0,erone(a,a,c));
	ASSERT_EQUAL(0,erone(a,a,a));

	a = Point(1, 3);
	b = Point(2,1);
	c = Point(4, 2);
	ASSERT_EQUAL(2.5,erone(a,b,c));
	ASSERT_EQUAL(2.5,erone(b,a,c));
	ASSERT_EQUAL(2.5,erone(c,a,b));
	ASSERT_EQUAL(0,erone(a,a,c));
}


void inLinePointsTest_01(){
	ASSERT_EQUAL(true,inLinePoints(1, 2, 3, 4, 5, 6 ));
}


void inLinePointsTest_02(){
	ASSERT_EQUAL(true,inLinePoints(1, 2, 1, 4, 1, 6 ));
}


void inLinePointsTest_03(){
	ASSERT_EQUAL(true,inLinePoints(1, 2, 3, 2, 5, 2 ));
}


void inLinePointsTest_04(){
	ASSERT_EQUAL(true,inLinePoints(0, 0, -1, -2, 2, 4 ));
}


void inLinePointsTest_05(){
	ASSERT_EQUAL(false,inLinePoints(0, 0, -1, -2, 2, 9 ));
}


void inLinePointsTest_06(){
	ASSERT_EQUAL(false,inLinePoints(0, 1, -1, -2, 2, 90 ));
}


void distanceTest_01(){
	Point a = Point(0,0);
	Point b = Point(1,0);

	ASSERT_EQUAL(1,myDistance(a,b));
}


void distanceTest_02(){
	Point a = Point(0,0);
	Point b = Point(-1,0);

	ASSERT_EQUAL(1,myDistance(a,b));
}


void distanceTest_04(){
	Point a = Point(0,0);
	Point b = Point(0,1);

	ASSERT_EQUAL(1,myDistance(a,b));
}


void distanceTest_03(){
	Point a = Point(0,0);
	Point b = Point(0,-1);

	ASSERT_EQUAL(1,myDistance(a,b));
}


void distanceTest_05(){
	Point a = Point(1,0);
	Point b = Point(0,0);

	ASSERT_EQUAL(1,myDistance(a,b));
}



void distanceTest_06(){
	Point a = Point(-1,0);
	Point b = Point(0,0);

	ASSERT_EQUAL(1,myDistance(a,b));
}


void distanceTest_07(){
	Point a = Point(1,0);
	Point b = Point(0,1);

	ASSERT_EQUAL(sqrt(2),myDistance(a,b));
}



void distanceTest_08(){
	Point a = Point(-1,-1);
	Point b = Point(1,1);

	ASSERT_EQUAL(2*sqrt(2),myDistance(a,b));
}



void distanceTest_09(){
	Point a = Point(-1,-1);
	Point b = Point(-1,-1);

	ASSERT_EQUAL(0,myDistance(a,b));
}


void distanceTest_10(){
	Point a = Point(-1,-1);
	Point b = Point(-2,-1);

	ASSERT_EQUAL(1,myDistance(a,b));
}


void areSameTest_01(){
	double a,b;

	a = 1.0;
	b = 1.0;

	ASSERT_EQUAL(true,areSame(a,b));
}



void areSameTest_02(){
	double a,b;

	a = 1.0;
	b = 2.0;

	ASSERT_EQUAL(false,areSame(a,b));
}



void areSameTest_03(){
	double a,b;

	a = 1.00000;
	b = 1.00010;

	ASSERT_EQUAL(false,areSame(a,b));
}



void areSameTest_04(){
	double a,b;

	a = 1.00000;
	b = 1.00001;

	ASSERT_EQUAL(false,areSame(a,b));
}


void areSameTest_05(){
	double a,b;

	a = 1.000000;
	b = 1.000001;

	ASSERT_EQUAL(true,areSame(a,b));
}



void areSameTest_06(){
	double a,b;

	a = 1.000000;
	b = 1.000009;

	ASSERT_EQUAL(true,areSame(a,b));
}


cute::suite make_suite_utilsTest(){
	cute::suite s;
	s.push_back(CUTE(utilsTest01));
	s.push_back(CUTE(utilsTest02));
	s.push_back(CUTE(utilsTest04));

	s.push_back(CUTE(inLinePointsTest_01));
	s.push_back(CUTE(inLinePointsTest_02));
	s.push_back(CUTE(inLinePointsTest_03));
	s.push_back(CUTE(inLinePointsTest_04));
	s.push_back(CUTE(inLinePointsTest_05));
	s.push_back(CUTE(inLinePointsTest_06));
	s.push_back(CUTE(distanceTest_01));
	s.push_back(CUTE(distanceTest_02));
	s.push_back(CUTE(distanceTest_03));
	s.push_back(CUTE(distanceTest_04));
	s.push_back(CUTE(distanceTest_05));
	s.push_back(CUTE(distanceTest_06));
	s.push_back(CUTE(distanceTest_07));
	s.push_back(CUTE(distanceTest_08));
	s.push_back(CUTE(distanceTest_09));
	s.push_back(CUTE(distanceTest_10));
	s.push_back(CUTE(areSameTest_01));
	s.push_back(CUTE(areSameTest_02));
	s.push_back(CUTE(areSameTest_03));
	s.push_back(CUTE(areSameTest_04));
	s.push_back(CUTE(areSameTest_05));
	s.push_back(CUTE(areSameTest_06));

	return s;
}

