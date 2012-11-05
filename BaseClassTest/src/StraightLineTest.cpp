#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "StraightLineTest.h"


void StraightLineTestFirstConstructor01(){
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

	ASSERT_EQUAL(l->isVertical(), actualIsVertical);

	ASSERT_EQUAL(true,l->doesPointBelongTo(0,0));

	ASSERT_EQUAL(false,l->doesPointBelongTo(1,1));
}


void StraightLineTestFirstConstructor02(){
	double actualA = 1;
	double actualB = 0;
	double actualC = 5;
	double actualSlope = 0;
	double actualIntercept = -actualC;
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

	ASSERT_EQUAL(l->isVertical(), actualIsVertical);

	ASSERT_EQUAL(true,l->doesPointBelongTo(0,-5));

	ASSERT_EQUAL(false,l->doesPointBelongTo(1,1));
}


void StraightLineTestFirstConstructor03(){
	double actualA = 0;
	double actualB = 1;
	double actualC = 5;
	//double actualSlope = -1;
	//double actualIntercept = 0;
	bool actualIsVertical = true;
	StraightLine *l = new StraightLine(actualA,actualB,actualC);

	double a = l->getA();
	ASSERT_EQUAL(a, actualA);

	double b = l->getB();
	ASSERT_EQUAL(b, actualB);

	double c = l->getC();
	ASSERT_EQUAL(c, actualC);

	ASSERT_THROWS(l->getSlope(),VerticalLineException);

	ASSERT_THROWS(l->getIntercept(), VerticalLineException);

	ASSERT_EQUAL(l->isVertical(), actualIsVertical);

	ASSERT_EQUAL(true,l->doesPointBelongTo(-5,0));

	ASSERT_EQUAL(false,l->doesPointBelongTo(1,1));
}


void StraightLineTestSecondConstructor01(){
	int xa = 1, ya = 1;
	int xb = -1, yb = -1;

	double actualA = -2;
	double actualB = 2;
	double actualC = 0;
	double actualSlope = 1;
	double actualIntercept = 0;
	bool actualIsVertical = false;
	StraightLine *l = new StraightLine(xa,ya,xb,yb);

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

	ASSERT_EQUAL(l->isVertical(), actualIsVertical);

	ASSERT_EQUAL(true,l->doesPointBelongTo(0,0));

	ASSERT_EQUAL(false,l->doesPointBelongTo(1,2));
}


void StraightLineTestSecondConstructor02(){
	int xa = 0, ya = 5;
	int xb = 5, yb = 5;

	double actualA = 5;
	double actualB = 0;
	double actualC = -25;
	double actualSlope = 0;
	double actualIntercept = 5;
	bool actualIsVertical = false;
	StraightLine *l = new StraightLine(xa,ya,xb,yb);

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

	ASSERT_EQUAL(l->isVertical(), actualIsVertical);

	ASSERT_EQUAL(true,l->doesPointBelongTo(1,5));

	ASSERT_EQUAL(false,l->doesPointBelongTo(0,0));
}


void StraightLineTestSecondConstructor03(){
	int xa = 5, ya = 0;
	int xb = 5, yb = 5;

	double actualA = 0;
	double actualB = 1;
	double actualC = -5;
	//double actualSlope = 0;
	//double actualIntercept = 5;
	bool actualIsVertical = true;
	StraightLine *l = new StraightLine(xa,ya,xb,yb);

	double a = l->getA();
	ASSERT_EQUAL(a, actualA);

	double b = l->getB();
	ASSERT_EQUAL(b, actualB);

	double c = l->getC();
	ASSERT_EQUAL(c, actualC);

	ASSERT_THROWS(l->getSlope(),VerticalLineException);

	ASSERT_THROWS(l->getIntercept(), VerticalLineException);

	ASSERT_EQUAL(l->isVertical(), actualIsVertical);

	ASSERT_EQUAL(true,l->doesPointBelongTo(5,1));

	ASSERT_EQUAL(false,l->doesPointBelongTo(0,0));
}


void StraightLineTestSecondConstructor04(){
	int xa = 5, ya = 5;
	int xb = 5, yb = 5;

	ASSERT_THROWS(StraightLine(xa,ya,xb,yb),InputException);

}


cute::suite make_suite_StraightLineTest(){
	cute::suite s;
	//s.push_back(CUTE(thisIsAStraightLineTestTest));
	s.push_back(CUTE(StraightLineTestFirstConstructor01));
	s.push_back(CUTE(StraightLineTestFirstConstructor02));
	s.push_back(CUTE(StraightLineTestFirstConstructor03));
	s.push_back(CUTE(StraightLineTestSecondConstructor01));
	s.push_back(CUTE(StraightLineTestSecondConstructor02));
	s.push_back(CUTE(StraightLineTestSecondConstructor03));
	s.push_back(CUTE(StraightLineTestSecondConstructor04));
	return s;
}



