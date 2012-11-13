#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "utilsTest.h"
#include <opencv/cv.h>
#include <vector>
#include <cmath>

void utilsTest01(){
	CvPoint a = cvPoint(1, 1);
	CvPoint b = cvPoint(-1, -1);
	CvPoint d = cvPoint(-1, 1);
	CvPoint c = cvPoint(1, -1);

	std::vector<CvPoint> coords;
	coords.push_back(a);
	coords.push_back(b);
	coords.push_back(c);
	coords.push_back(d);
	std::vector<CvPoint> sorted = Sort4PointsClockwise(coords);

	std::stringstream out;

	out << sorted[0].x << sorted[0].y ;
	out << sorted[1].x << sorted[1].y ;
	out << sorted[2].x << sorted[2].y ;
	out << sorted[3].x << sorted[3].y ;
	ASSERT_EQUAL("111-1-1-1-11",out.str());
}

void utilsTest02(){
	CvPoint a = cvPoint(10, 22);
	CvPoint b = cvPoint(-12, 11);
	CvPoint d = cvPoint(-1, -6);
	CvPoint c = cvPoint(0, -4);

	std::vector<CvPoint> coords;
	coords.push_back(a);
	coords.push_back(b);
	coords.push_back(c);
	coords.push_back(d);

	ASSERT_EQUAL(10,getMinMax(coords, MAX_X));
	ASSERT_EQUAL(22,getMinMax(coords, MAX_Y));
	ASSERT_EQUAL(-12,getMinMax(coords, MIN_X));
	ASSERT_EQUAL(-6,getMinMax(coords, MIN_Y));
}

void utilsTest03(){
	ASSERT_EQUAL(true,inLinePoints(1, 2, 3, 4, 5, 6 ));
	ASSERT_EQUAL(true,inLinePoints(1, 2, 1, 4, 1, 6 ));
	ASSERT_EQUAL(true,inLinePoints(1, 2, 3, 2, 5, 2 ));
	ASSERT_EQUAL(true,inLinePoints(0, 0, -1, -2, 2, 4 ));
	ASSERT_EQUAL(false,inLinePoints(0, 0, -1, -2, 2, 9 ));
	ASSERT_EQUAL(false,inLinePoints(0, 1, -1, -2, 2, 90 ));
}

void utilsTest04(){
	CvPoint a = cvPoint(0, 0);
	CvPoint b = cvPoint(1,0);
	CvPoint c = cvPoint(0, 2);

	ASSERT_EQUAL(1,erone(a,b,c));
	ASSERT_EQUAL(1,erone(b,a,c));
	ASSERT_EQUAL(1,erone(c,a,b));
	ASSERT_EQUAL(0,erone(a,a,c));

	a = cvPoint(1, 3);
	b = cvPoint(2,1);
	c = cvPoint(4, 2);
	ASSERT_EQUAL(2.5,erone(a,b,c));
	ASSERT_EQUAL(2.5,erone(b,a,c));
	ASSERT_EQUAL(2.5,erone(c,a,b));
	ASSERT_EQUAL(0,erone(a,a,c));
}

cute::suite make_suite_utilsTest(){
	cute::suite s;
	s.push_back(CUTE(utilsTest01));
	s.push_back(CUTE(utilsTest02));
	s.push_back(CUTE(utilsTest03));
	s.push_back(CUTE(utilsTest04));

	return s;
}

