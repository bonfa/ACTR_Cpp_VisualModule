#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "SegmentTest.h"

struct ConstructorError {

	void ConstructorError_01(){
			Point p1 = Point(0,0);
			Point p2 = Point(0,0);
			ASSERT_THROWS(new Segment(p1,p2),InputException);
		}

	void ConstructorError_02(){
		Point p1 = Point(1,3);
		Point p2 = Point(1,3);
		ASSERT_THROWS(new Segment(p1,p2),InputException);
	}
};


struct SegmentTest_01{

	SegmentTest_01(): s(Point(0,0),Point(3,3)){
		expectedA = Point(0,0);
		expectedB = Point(3,3);
		expectedPointList.push_back(expectedA);
		expectedPointList.push_back(expectedB);
	}

	void getPointsTest(){
		std::vector<Point> pointList = s.getPoints();
		ASSERT_EQUAL(expectedPointList,pointList);
	}

	void getInterceptionPointParallel(){
		Segment s2 = Segment(Point(0,1),Point(3,4));
		ASSERT_THROWS(s.getInterceptionPoint(s2),NotOverlappedSegmentException);
	}

	void getInterceptionPointNotOverlapped(){
		Segment s2 = Segment(Point(-1,0),Point(-3,0));
		ASSERT_THROWS(s.getInterceptionPoint(s2),NotOverlappedSegmentException);
	}

	void getInterceptionPoint_01(){
		Segment s2 = Segment(Point(2,0),Point(2,4));
		Point interception = s.getInterceptionPoint(s2);
		ASSERT_EQUAL(interception,Point(2,2));
	}

	void getInterceptionPoint_02(){
		Segment s2 = Segment(Point(1,0),Point(0,1));
		Point interception = s.getInterceptionPoint(s2);
		ASSERT_EQUAL(interception,Point(1,1));
	}

	void getInterceptionBorderline_01(){
		Segment s2 = Segment(Point(0,0),Point(-2,0));
		Point interception = s.getInterceptionPoint(s2);
		ASSERT_EQUAL(interception,Point(0,0));
	}

	void getInterceptionBorderline_02(){
		Segment s2 = Segment(Point(3,3),Point(-2,0));
		Point interception = s.getInterceptionPoint(s2);
		ASSERT_EQUAL(interception,Point(3,3));
	}

	void isPointBetweenSegmentExtremes_01(){
		Point p = Point(0,2);
		ASSERT_EQUAL(true,s.isPointBetweenSegmentExtremes(p));
	}

	void isPointBetweenSegmentExtremes_02(){
		Point p = Point(2,2);
		ASSERT_EQUAL(true,s.isPointBetweenSegmentExtremes(p));
	}

	void isPointBetweenSegmentExtremes_03(){
		Point p = Point(2,0);
		ASSERT_EQUAL(true,s.isPointBetweenSegmentExtremes(p));
	}

	void isPointBetweenSegmentExtremes_04(){
		Point p = Point(3,0);
		ASSERT_EQUAL(true,s.isPointBetweenSegmentExtremes(p));
	}

	void isPointBetweenSegmentExtremes_05(){
		Point p = Point(0,3);
		ASSERT_EQUAL(true,s.isPointBetweenSegmentExtremes(p));
	}

	void isPointBetweenSegmentExtremes_06(){
		Point p = Point(-1,0);
		ASSERT_EQUAL(false,s.isPointBetweenSegmentExtremes(p));
	}

	void isPointBetweenSegmentExtremes_07(){
		Point p = Point(-1,1);
		ASSERT_EQUAL(false,s.isPointBetweenSegmentExtremes(p));
	}

	void isPointBetweenSegmentExtremes_08(){
		Point p = Point(-1,4);
		ASSERT_EQUAL(false,s.isPointBetweenSegmentExtremes(p));
	}

	void isPointBetweenSegmentExtremes_09(){
		Point p = Point(1,4);
		ASSERT_EQUAL(false,s.isPointBetweenSegmentExtremes(p));
	}

	void isPointBetweenSegmentExtremes_10(){
		Point p = Point(8,8);
		ASSERT_EQUAL(false,s.isPointBetweenSegmentExtremes(p));
	}

	void isPointBetweenSegmentExtremes_11(){
		Point p = Point(12,2);
		ASSERT_EQUAL(false,s.isPointBetweenSegmentExtremes(p));
	}

	void isPointBetweenSegmentExtremes_12(){
		Point p = Point(12,-2);
		ASSERT_EQUAL(false,s.isPointBetweenSegmentExtremes(p));
	}

	void isPointBetweenSegmentExtremes_13(){
		Point p = Point(2,-1);
		ASSERT_EQUAL(false,s.isPointBetweenSegmentExtremes(p));
	}

	void isPointBetweenSegmentExtremes_14(){
		Point p = Point(-2,-1);
		ASSERT_EQUAL(false,s.isPointBetweenSegmentExtremes(p));
	}

	void isEqual_01(){
		Segment s2 = Segment(Point(0,0),Point(3,3));
		ASSERT_EQUAL(true,s == s2);
	}

	void isEqual_02(){
		Segment s2 = Segment(Point(3,3),Point(0,0));
		ASSERT_EQUAL(true,s == s2);
	}

	void isEqual_03(){
		Segment s2 = Segment(Point(1,1),Point(0,0));
		ASSERT_EQUAL(false,s == s2);
	}

	void isEqual_04(){
		Segment s2 = Segment(Point(0,0),Point(1,1));
		ASSERT_EQUAL(false,s == s2);
	}

	void isEqual_05(){
		Segment s2 = Segment(Point(0,1),Point(3,4));
		ASSERT_EQUAL(false,s == s2);
	}

	void isEqual_06(){
		Segment s2 = Segment(Point(5,5),Point(2,3));
		ASSERT_EQUAL(false,s == s2);
	}

	Segment s;
	Point expectedA;
	Point expectedB;
	std::vector<Point> expectedPointList;

};

//TODO: tests


cute::suite make_suite_SegmentTest(){
	cute::suite s;

	s+= CUTE_SMEMFUN(ConstructorError,ConstructorError_01);
	s+= CUTE_SMEMFUN(ConstructorError,ConstructorError_02);

	s+= CUTE_SMEMFUN(SegmentTest_01,getPointsTest);
	s+= CUTE_SMEMFUN(SegmentTest_01,getInterceptionPointParallel);
	s+= CUTE_SMEMFUN(SegmentTest_01,getInterceptionPointNotOverlapped);
	s+= CUTE_SMEMFUN(SegmentTest_01,getInterceptionPoint_01);
	s+= CUTE_SMEMFUN(SegmentTest_01,getInterceptionPoint_02);
	s+= CUTE_SMEMFUN(SegmentTest_01,getInterceptionBorderline_01);
	s+= CUTE_SMEMFUN(SegmentTest_01,getInterceptionBorderline_02);
	s+= CUTE_SMEMFUN(SegmentTest_01,isPointBetweenSegmentExtremes_01);
	s+= CUTE_SMEMFUN(SegmentTest_01,isPointBetweenSegmentExtremes_02);
	s+= CUTE_SMEMFUN(SegmentTest_01,isPointBetweenSegmentExtremes_03);
	s+= CUTE_SMEMFUN(SegmentTest_01,isPointBetweenSegmentExtremes_04);
	s+= CUTE_SMEMFUN(SegmentTest_01,isPointBetweenSegmentExtremes_05);
	s+= CUTE_SMEMFUN(SegmentTest_01,isPointBetweenSegmentExtremes_06);
	s+= CUTE_SMEMFUN(SegmentTest_01,isPointBetweenSegmentExtremes_07);
	s+= CUTE_SMEMFUN(SegmentTest_01,isPointBetweenSegmentExtremes_08);
	s+= CUTE_SMEMFUN(SegmentTest_01,isPointBetweenSegmentExtremes_09);
	s+= CUTE_SMEMFUN(SegmentTest_01,isPointBetweenSegmentExtremes_10);
	s+= CUTE_SMEMFUN(SegmentTest_01,isPointBetweenSegmentExtremes_11);
	s+= CUTE_SMEMFUN(SegmentTest_01,isPointBetweenSegmentExtremes_12);
	s+= CUTE_SMEMFUN(SegmentTest_01,isPointBetweenSegmentExtremes_13);
	s+= CUTE_SMEMFUN(SegmentTest_01,isPointBetweenSegmentExtremes_14);
	s+= CUTE_SMEMFUN(SegmentTest_01,isEqual_01);
	s+= CUTE_SMEMFUN(SegmentTest_01,isEqual_02);
	s+= CUTE_SMEMFUN(SegmentTest_01,isEqual_03);
	s+= CUTE_SMEMFUN(SegmentTest_01,isEqual_04);
	s+= CUTE_SMEMFUN(SegmentTest_01,isEqual_05);
	s+= CUTE_SMEMFUN(SegmentTest_01,isEqual_06);


	return s;
}



