#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "StraightLineTest.h"

void thisIsAStraightLineTestTest() {
	ASSERTM("start writing tests", false);
}

void StraightLineTest01(){
	double actualA = 1;
	double actualB = 1;
	double actualC = 0;
	double actualSlope = -1;
	double actualIntercept = 0;
	bool actualIsVertical = false;
	StraightLine *l = new StraightLine(actualA,actualB,actualC);

	double a = l->getA();
	ASSERT_EQUAL(a, actualA);

	double b = l->getB();
	ASSERT_EQUAL(b, actualB);

	double c = l->getC();
	ASSERT_EQUAL(c, actualC);

	double slope = l->getSlope();
	ASSERT_EQUAL(slope,actualSlope);

	double intercept = l->getIntercept();
	ASSERT_EQUAL(intercept, actualIntercept);

	ASSERT_EQUAL(false, actualIsVertical);

	ASSERT_EQUAL(true,l->doesPointBelongTo(0,0));

	ASSERT_EQUAL(false,l->doesPointBelongTo(1,1));
}



cute::suite make_suite_StraightLineTest(){
	cute::suite s;
	s.push_back(CUTE(thisIsAStraightLineTestTest));
	s.push_back(CUTE(StraightLineTest01));
	return s;
}



