#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "TriangleTest.h"


void TriangleTest_Constructor_01(){
	int ax = 1;
	int ay = 2;
	int bx = 3;
	int by = 4;
	int cx = 6;
	int cy = 5;

	Triangle *t = new Triangle(ax,ay,bx,by,cx,cy);
	ASSERT(t!=NULL);
}


void TriangleTest_Parameters_01(){
	int ax = 0;
	int ay = 0;
	int bx = 4;
	int by = 0;
	int cx = 2;
	int cy = 2;
	string expectedChunkString = "cianc, traingle\n";

	Triangle *t = new Triangle(ax,ay,bx,by,cx,cy);
	ASSERT_EQUAL(Point(ax,ay),t->getA());
	ASSERT_EQUAL(Point(bx,by),t->getB());
	ASSERT_EQUAL(Point(cx,cy),t->getC());
	ASSERT_EQUAL(4.0,t->getArea());
	Rect bbox = t->getBbox();
	ASSERT_EQUAL(Rect(0,0,2,4),bbox);
	ASSERT_EQUAL(expectedChunkString,t->getChunk());
}


void TriangleTest_Error_01(){
	int ax = -1;
	int ay = 2;
	int bx = 3;
	int by = 4;
	int cx = 5;
	int cy = 6;

	ASSERT_THROWS(new Triangle(ax,ay,bx,by,cx,cy),InputException);
}


void TriangleTest_Error_02(){
	int ax = 1;
	int ay = -2;
	int bx = 3;
	int by = 4;
	int cx = 5;
	int cy = 6;

	ASSERT_THROWS(new Triangle(ax,ay,bx,by,cx,cy),InputException);
}


void TriangleTest_Error_03(){
	int ax = 1;
	int ay = 2;
	int bx = -3;
	int by = 4;
	int cx = 5;
	int cy = 6;

	ASSERT_THROWS(new Triangle(ax,ay,bx,by,cx,cy),InputException);
}


void TriangleTest_Error_04(){
	int ax = 1;
	int ay = 2;
	int bx = 3;
	int by = -4;
	int cx = 5;
	int cy = 6;

	ASSERT_THROWS(new Triangle(ax,ay,bx,by,cx,cy),InputException);
}


void TriangleTest_Error_05(){
	int ax = 1;
	int ay = 2;
	int bx = 3;
	int by = 4;
	int cx = -5;
	int cy = 6;

	ASSERT_THROWS(new Triangle(ax,ay,bx,by,cx,cy),InputException);
}


void TriangleTest_Error_06(){
	int ax = -1;
	int ay = 2;
	int bx = 3;
	int by = 4;
	int cx = 5;
	int cy = -6;

	ASSERT_THROWS(new Triangle(ax,ay,bx,by,cx,cy),InputException);
}


void TriangleTest_Error_07(){
	int ax = 1;
	int ay = 2;
	int bx = 3;
	int by = 4;
	int cx = 5;
	int cy = 6;

	ASSERT_THROWS(new Triangle(ax,ay,bx,by,cx,cy),InputException);
}



cute::suite make_suite_TriangleTest(){
	cute::suite s;
	s.push_back(CUTE(TriangleTest_Constructor_01));
	s.push_back(CUTE(TriangleTest_Parameters_01));
	s.push_back(CUTE(TriangleTest_Error_01));
	s.push_back(CUTE(TriangleTest_Error_02));
	s.push_back(CUTE(TriangleTest_Error_03));
	s.push_back(CUTE(TriangleTest_Error_04));
	s.push_back(CUTE(TriangleTest_Error_05));
	s.push_back(CUTE(TriangleTest_Error_06));
	s.push_back(CUTE(TriangleTest_Error_07));
	return s;
}



