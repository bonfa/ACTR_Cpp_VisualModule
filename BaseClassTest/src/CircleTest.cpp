#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "CircleTest.h"


void CircleTest_Constructor_01(){
	int ax = 5;
	int ay = 5;
	int radius = 3;

	Circle *c = new Circle(radius,ax,ay);
	ASSERT(c!=NULL);
}


void CircleTest_ParametersTest_01(){
	int ax = 5;
	int ay = 6;
	int radius = 3;
	string expectedChunkString = "cianc, Circle\n";

	Circle *c = new Circle(radius,ax,ay);
	ASSERT_EQUAL(ax,c->getXCenter());
	ASSERT_EQUAL(ay,c->getYCenter());
	ASSERT_EQUAL(radius,c->getRadius());
	ASSERT_EQUAL(expectedChunkString,c->getChunk());
}


void CircleTest_Errors_01(){
	int ax = -1;
	int ay = 6;
	int radius = 3;

	ASSERT_THROWS(new Circle(radius,ax,ay),InputException);
}


void CircleTest_Errors_02(){
	int ax = 1;
	int ay = -6;
	int radius = 3;

	ASSERT_THROWS(new Circle(radius,ax,ay),InputException);
}


void CircleTest_Errors_03(){
	int ax = 5;
	int ay = 6;
	int radius = -3;

	ASSERT_THROWS(new Circle(radius,ax,ay),InputException);
}


cute::suite make_suite_CircleTest(){
	cute::suite s;
	s.push_back(CUTE(CircleTest_Constructor_01));
	s.push_back(CUTE(CircleTest_ParametersTest_01));
	s.push_back(CUTE(CircleTest_Errors_01));
	s.push_back(CUTE(CircleTest_Errors_02));
	s.push_back(CUTE(CircleTest_Errors_03));
	return s;
}



