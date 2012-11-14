#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "QuadrilateralTest.h"


void QuadrilateralTest_Constructor_01(){
	int ax = 0;
	int ay = 0;
	int bx = 2;
	int by = 0;
	int cx = 2;
	int cy = 2;
	int dx = 0;
	int dy = 2;

	Quadrilateral *q = new Quadrilateral(ax,ay,bx,by,cx,cy,dx,dy);
	ASSERT(q!=NULL);
}


void QuadrilateralTest_Parameters_01(){
	int ax = 0;
	int ay = 0;
	int bx = 2;
	int by = 0;
	int cx = 2;
	int cy = 3;
	int dx = 0;
	int dy = 3;
	string expectedChunkString = "cianc, Quadrilateral\n";

	Quadrilateral *q = new Quadrilateral(ax,ay,bx,by,cx,cy,dx,dy);
	ASSERT_EQUAL(Point(ax,ay),q->getA());
	ASSERT_EQUAL(Point(bx,by),q->getB());
	ASSERT_EQUAL(Point(cx,cy),q->getC());
	ASSERT_EQUAL(Point(dx,dy),q->getD());
	ASSERT_EQUAL(6.0,q->getArea());
	Rect bbox = q->getBbox();
	ASSERT_EQUAL(Rect(0,0,3,2),bbox);
	ASSERT_EQUAL(expectedChunkString,q->getChunk());
}


void QuadrilateralTest_Error_01(){
	int ax = -1;
	int ay = 0;
	int bx = 2;
	int by = 0;
	int cx = 2;
	int cy = 3;
	int dx = 0;
	int dy = 3;

	ASSERT_THROWS(new Quadrilateral(ax,ay,bx,by,cx,cy,dx,dy),InputException);
}


void QuadrilateralTest_Error_02(){
	int ax = 0;
	int ay = -1;
	int bx = 2;
	int by = 0;
	int cx = 2;
	int cy = 3;
	int dx = 0;
	int dy = 3;

	ASSERT_THROWS(new Quadrilateral(ax,ay,bx,by,cx,cy,dx,dy),InputException);
}


void QuadrilateralTest_Error_03(){
	int ax = 0;
	int ay = 0;
	int bx = -2;
	int by = 0;
	int cx = 2;
	int cy = 3;
	int dx = 0;
	int dy = 3;

	ASSERT_THROWS(new Quadrilateral(ax,ay,bx,by,cx,cy,dx,dy),InputException);
}


void QuadrilateralTest_Error_04(){
	int ax = 0;
	int ay = 0;
	int bx = 2;
	int by = -1;
	int cx = 2;
	int cy = 3;
	int dx = 0;
	int dy = 3;

	ASSERT_THROWS(new Quadrilateral(ax,ay,bx,by,cx,cy,dx,dy),InputException);
}


void QuadrilateralTest_Error_05(){
	int ax = 0;
	int ay = 0;
	int bx = 2;
	int by = 0;
	int cx = -2;
	int cy = 3;
	int dx = 0;
	int dy = 3;

	ASSERT_THROWS(new Quadrilateral(ax,ay,bx,by,cx,cy,dx,dy),InputException);
}


void QuadrilateralTest_Error_06(){
	int ax = 0;
	int ay = 0;
	int bx = 2;
	int by = 0;
	int cx = 2;
	int cy = -3;
	int dx = 0;
	int dy = 3;

	ASSERT_THROWS(new Quadrilateral(ax,ay,bx,by,cx,cy,dx,dy),InputException);
}


void QuadrilateralTest_Error_07(){
	int ax = 0;
	int ay = 0;
	int bx = 2;
	int by = 0;
	int cx = 2;
	int cy = 3;
	int dx = -1;
	int dy = 3;

	ASSERT_THROWS(new Quadrilateral(ax,ay,bx,by,cx,cy,dx,dy),InputException);
}


void QuadrilateralTest_Error_08(){
	int ax = 0;
	int ay = 0;
	int bx = 2;
	int by = 0;
	int cx = 2;
	int cy = 3;
	int dx = 0;
	int dy = -3;

	ASSERT_THROWS(new Quadrilateral(ax,ay,bx,by,cx,cy,dx,dy),InputException);
}


void QuadrilateralTest_Allineated_Error_01(){
	int ax = 0;
	int ay = 0;
	int bx = 0;
	int by = 0;
	int cx = 0;
	int cy = 0;
	int dx = 1;
	int dy = 12;

	ASSERT_THROWS(new Quadrilateral(ax,ay,bx,by,cx,cy,dx,dy),InputException);
}


void QuadrilateralTest_Allineated_Error_02(){
	int ax = 0;
	int ay = 0;
	int bx = 0;
	int by = 0;
	int cx = 1;
	int cy = 1;
	int dx = 0;
	int dy = 0;

	ASSERT_THROWS(new Quadrilateral(ax,ay,bx,by,cx,cy,dx,dy),InputException);
}


void QuadrilateralTest_Allineated_Error_03(){
	int ax = 0;
	int ay = 0;
	int bx = 1;
	int by = 1;
	int cx = 0;
	int cy = 0;
	int dx = 0;
	int dy = 0;

	ASSERT_THROWS(new Quadrilateral(ax,ay,bx,by,cx,cy,dx,dy),InputException);
}


void QuadrilateralTest_Allineated_Error_04(){
	int ax = 1;
	int ay = 1;
	int bx = 0;
	int by = 0;
	int cx = 0;
	int cy = 0;
	int dx = 0;
	int dy = 0;

	ASSERT_THROWS(new Quadrilateral(ax,ay,bx,by,cx,cy,dx,dy),InputException);
}


void QuadrilateralTest_CoincidentPoints_Error_01(){
	int ax = 1;
	int ay = 1;
	int bx = 0;
	int by = 0;
	int cx = 1;
	int cy = 1;
	int dx = 0;
	int dy = 0;

	ASSERT_THROWS(new Quadrilateral(ax,ay,bx,by,cx,cy,dx,dy),InputException);
}




cute::suite make_suite_QuadrilateralTest(){
	cute::suite s;
	s.push_back(CUTE(QuadrilateralTest_Constructor_01));
	s.push_back(CUTE(QuadrilateralTest_Parameters_01));
	s.push_back(CUTE(QuadrilateralTest_Allineated_Error_01));
	s.push_back(CUTE(QuadrilateralTest_Allineated_Error_02));
	s.push_back(CUTE(QuadrilateralTest_Allineated_Error_03));
	s.push_back(CUTE(QuadrilateralTest_Allineated_Error_04));
	s.push_back(CUTE(QuadrilateralTest_CoincidentPoints_Error_01));
	s.push_back(CUTE(QuadrilateralTest_Error_01));
	s.push_back(CUTE(QuadrilateralTest_Error_02));
	s.push_back(CUTE(QuadrilateralTest_Error_03));
	s.push_back(CUTE(QuadrilateralTest_Error_04));
	s.push_back(CUTE(QuadrilateralTest_Error_05));
	s.push_back(CUTE(QuadrilateralTest_Error_06));
	s.push_back(CUTE(QuadrilateralTest_Error_07));
	s.push_back(CUTE(QuadrilateralTest_Error_08));
	return s;
}



