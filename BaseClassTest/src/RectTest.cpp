#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "RectTest.h"


struct ConstructorError{
	void ParameterError_01() {
		int x = -1;
		int y = 0;
		int height = 1;
		int width = 1;

		ASSERT_THROWS(new Rect(x,y,height,width),InputException);
	}


	void ParameterError_02() {
		int x = 0;
		int y = -1;
		int height = 1;
		int width = 1;

		ASSERT_THROWS(new Rect(x,y,height,width),InputException);
	}


	void ParameterError_03() {
		int x = 0;
		int y = 0;
		int height = 0;
		int width = 1;

		ASSERT_THROWS(new Rect(x,y,height,width),InputException);
	}


	void ParameterError_04() {
		int x = 0;
		int y = 0;
		int height = 1;
		int width = 0;

		ASSERT_THROWS(new Rect(x,y,height,width),InputException);
	}
};


struct RectTest_01{

	RectTest_01(): r(){
		expectedPointList.push_back(Point(0,0));
		expectedPointList.push_back(Point(0,0));
		expectedPointList.push_back(Point(0,0));
		expectedPointList.push_back(Point(0,0));
	}

	void Constructor(){
		ASSERT_EQUAL(false, (&r)==NULL);
	}

	void checkX() {
		ASSERT_EQUAL(0,r.x);
	}

	void checkY() {
		ASSERT_EQUAL(0,r.y);
	}

	void checkHeight() {
		ASSERT_EQUAL(0,r.height);
	}

	void checkWidth() {
		ASSERT_EQUAL(0,r.width);
	}

	void checkEqual_01() {
		Rect *r2 = new Rect();
		ASSERT_EQUAL(r,*r2);
	}

	void checkEqual_02() {
		Rect *r2 = new Rect();
		ASSERT_EQUAL(true,r==*r2);
	}

	void checkEqual_03() {
		Rect r2(5,5,5,5);
		ASSERT_EQUAL(false,r==r2);
	}

	void checkGetPoints(){
		std::vector<Point> pointList = r.getPoints();
		ASSERT_EQUAL(expectedPointList,pointList);
	}

	void checkGetEdgeLines(){
		ASSERT_THROWS(r.getEdgesLine(),InputException);
	}


	Rect r;
	std::vector<Point> expectedPointList;
};


struct RectTest_02{

	RectTest_02(): r(4,3,7,5){
		Point p1(4,3);
		Point p2(9,3);
		Point p3(9,10);
		Point p4(4,10);
		expectedPointList.push_back(p1);
		expectedPointList.push_back(p2);
		expectedPointList.push_back(p3);
		expectedPointList.push_back(p4);
		expectedEdgeList.push_back(Segment(p1,p2));
		expectedEdgeList.push_back(Segment(p2,p3));
		expectedEdgeList.push_back(Segment(p3,p4));
		expectedEdgeList.push_back(Segment(p4,p1));
	}

	void Constructor(){
		ASSERT_EQUAL(false, (&r)==NULL);
	}

	void checkX() {
		ASSERT_EQUAL(4,r.x);
	}

	void checkY() {
		ASSERT_EQUAL(3,r.y);
	}

	void checkHeight() {
		ASSERT_EQUAL(7,r.height);
	}

	void checkWidth() {
		ASSERT_EQUAL(5,r.width);
	}

	void checkEqual_01() {
		Rect *r2 = new Rect(4,3,7,5);
		ASSERT_EQUAL(r,*r2);
	}

	void checkEqual_02() {
		Rect *r2 = new Rect(4,3,7,5);
		ASSERT_EQUAL(true,r==*r2);
	}

	void checkEqual_03() {
		Rect r2(5,5,5,5);
		ASSERT_EQUAL(false,r==r2);
	}

	void checkGetPoints(){
		std::vector<Point> pointList = r.getPoints();
		ASSERT_EQUAL(expectedPointList,pointList);
	}

	void checkGetEdgeLines(){
		std::vector<Segment> edgeList = r.getEdgesLine();
		ASSERT_EQUAL(expectedEdgeList,edgeList);
	}

	Rect r;
	std::vector<Point> expectedPointList;
	std::vector<Segment> expectedEdgeList;
};




cute::suite make_suite_RectTest(){
	cute::suite s;

	s+= CUTE_SMEMFUN(ConstructorError,ParameterError_01);
	s+= CUTE_SMEMFUN(ConstructorError,ParameterError_02);
	s+= CUTE_SMEMFUN(ConstructorError,ParameterError_03);
	s+= CUTE_SMEMFUN(ConstructorError,ParameterError_04);

	s+= CUTE_SMEMFUN(RectTest_01,Constructor);
	s+= CUTE_SMEMFUN(RectTest_01,checkX);
	s+= CUTE_SMEMFUN(RectTest_01,checkY);
	s+= CUTE_SMEMFUN(RectTest_01,checkHeight);
	s+= CUTE_SMEMFUN(RectTest_01,checkWidth);
	s+= CUTE_SMEMFUN(RectTest_01,checkEqual_01);
	s+= CUTE_SMEMFUN(RectTest_01,checkEqual_02);
	s+= CUTE_SMEMFUN(RectTest_01,checkEqual_03);
	s+= CUTE_SMEMFUN(RectTest_01,checkGetPoints);
	s+= CUTE_SMEMFUN(RectTest_01,checkGetEdgeLines);


	s+= CUTE_SMEMFUN(RectTest_02,Constructor);
	s+= CUTE_SMEMFUN(RectTest_02,checkX);
	s+= CUTE_SMEMFUN(RectTest_02,checkY);
	s+= CUTE_SMEMFUN(RectTest_02,checkHeight);
	s+= CUTE_SMEMFUN(RectTest_02,checkWidth);
	s+= CUTE_SMEMFUN(RectTest_02,checkEqual_01);
	s+= CUTE_SMEMFUN(RectTest_02,checkEqual_02);
	s+= CUTE_SMEMFUN(RectTest_02,checkEqual_03);
	s+= CUTE_SMEMFUN(RectTest_02,checkGetPoints);
	s+= CUTE_SMEMFUN(RectTest_02,checkGetEdgeLines);


	return s;
}



