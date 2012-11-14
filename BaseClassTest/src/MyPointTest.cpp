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




cute::suite make_suite_MyPointTest(){
	cute::suite s;
	s.push_back(CUTE(PointTest_Constructor_01));
	s.push_back(CUTE(PointTest_Constructor_02));
	s.push_back(CUTE(PointTest_Constructor_03));
	s.push_back(CUTE(PointTest_ParametersCheck_01));
	s.push_back(CUTE(PointTest_ParametersCheck_02));

	return s;
}



