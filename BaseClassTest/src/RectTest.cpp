#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "RectTest.h"


void RectTest_Constructor_01(){
	Rect *r = new Rect();
	ASSERT(r!=NULL);
}


void RectTest_Constructor_02(){
	Rect *r = new Rect(4,4,4,4);
	ASSERT(r!=NULL);
}


void RectTest_ParameterCheck_01() {
	Rect *r = new Rect();
	ASSERT_EQUAL(0,r->x);
	ASSERT_EQUAL(0,r->y);
	ASSERT_EQUAL(0,r->height);
	ASSERT_EQUAL(0,r->width);
}


void RectTest_ParameterCheck_02() {
	int x = 0;
	int y = 0;
	int height = 2;
	int width = 1;

	Rect *r = new Rect(x,y,height,width);
	ASSERT_EQUAL(x,r->x);
	ASSERT_EQUAL(y,r->y);
	ASSERT_EQUAL(height,r->height);
	ASSERT_EQUAL(width,r->width);
}


void RectTest_ParameterError_01() {
	int x = -1;
	int y = 0;
	int height = 1;
	int width = 1;

	ASSERT_THROWS(new Rect(x,y,height,width),InputException);
}


void RectTest_ParameterError_02() {
	int x = 0;
	int y = -1;
	int height = 1;
	int width = 1;

	ASSERT_THROWS(new Rect(x,y,height,width),InputException);
}


void RectTest_ParameterError_03() {
	int x = 0;
	int y = 0;
	int height = 0;
	int width = 1;

	ASSERT_THROWS(new Rect(x,y,height,width),InputException);
}


void RectTest_ParameterError_04() {
	int x = 0;
	int y = 0;
	int height = 1;
	int width = 0;

	ASSERT_THROWS(new Rect(x,y,height,width),InputException);
}


void RectTest_Operator_01() {
	Rect *r1 = new Rect(4,4,4,4);
	Rect *r2 = new Rect(4,4,4,4);
	ASSERT_EQUAL(*r1,*r2);
}

void RectTest_Operator_02() {
	Rect *r1 = new Rect();
	Rect *r2 = new Rect();
	ASSERT_EQUAL(*r1,*r2);
}


cute::suite make_suite_RectTest(){
	cute::suite s;
	s.push_back(CUTE(RectTest_Constructor_01));
	s.push_back(CUTE(RectTest_Constructor_02));
	s.push_back(CUTE(RectTest_ParameterCheck_01));
	s.push_back(CUTE(RectTest_ParameterCheck_02));
	s.push_back(CUTE(RectTest_ParameterError_01));
	s.push_back(CUTE(RectTest_ParameterError_02));
	s.push_back(CUTE(RectTest_ParameterError_03));
	s.push_back(CUTE(RectTest_ParameterError_04));
	s.push_back(CUTE(RectTest_Operator_01));
	s.push_back(CUTE(RectTest_Operator_02));
	return s;
}



