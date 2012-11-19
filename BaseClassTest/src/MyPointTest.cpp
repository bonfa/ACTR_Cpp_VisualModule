#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "MyPointTest.h"


void PointTest_Constructor_01() {
	Point *p;
	ASSERT(p==NULL);
}


void PointTest_Constructor_02() {
	Point *p = new Point();
	ASSERT(p!=NULL);
}


void PointTest_Constructor_03() {
	Point *p = new Point(4,5);
	ASSERT(p!=NULL);
}


void PointTest_ParametersCheck_01() {
	Point *p = new Point();
	ASSERT_EQUAL(0, p->x);
	ASSERT_EQUAL(0, p->y);
}


void PointTest_ParametersCheck_02() {
	int ax = 5;
	int ay = 4;

	Point *p = new Point(ax,ay);
	ASSERT_EQUAL(ax, p->x);
	ASSERT_EQUAL(ay,p->y);
}


void PointTest_Operators_01(){
	int ax = 5;
	int ay = 4;
	Point *p1 = new Point(ax,ay);
	Point *p2 = new Point(ax,ay);
	ASSERT(*p1==*p2);
}


void PointTest_Operators_02(){
	int ax = 5;
	int ay = 4;
	Point *p1 = new Point(ax,ay);
	Point *p2 = new Point(ax,ay);
	ASSERT_EQUAL(*p1,*p2);
}


void PointTest_Operators_03(){
	Point p1 = Point(0,0);
	Point p2 = Point(0,0);
	ASSERT_EQUAL(p1,p2);
}

cute::suite make_suite_MyPointTest(){
	cute::suite s;
	s.push_back(CUTE(PointTest_Constructor_01));
	s.push_back(CUTE(PointTest_Constructor_02));
	s.push_back(CUTE(PointTest_Constructor_03));
	s.push_back(CUTE(PointTest_ParametersCheck_01));
	s.push_back(CUTE(PointTest_ParametersCheck_02));
	s.push_back(CUTE(PointTest_Operators_01));
	s.push_back(CUTE(PointTest_Operators_02));
	s.push_back(CUTE(PointTest_Operators_03));
	return s;
}



