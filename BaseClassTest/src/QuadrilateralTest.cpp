#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "QuadrilateralTest.h"

void QuadrilateralTest01(){
	int ax = 0;
	int ay = 0;
	int bx = 2;
	int by = 0;
	int cx = 2;
	int cy = 2;
	int dx = 0;
	int dy = 2;

	string actualChunkString = "cianc, Quadrilateral\n";
	Quadrilateral *q = new Quadrilateral(ax,ay,bx,by,cx,cy,dx,dy);
	string realChunkString = q->getChunk();
	ASSERT_EQUAL(actualChunkString,realChunkString);
}

cute::suite make_suite_QuadrilateralTest(){
	cute::suite s;
	s.push_back(CUTE(QuadrilateralTest01));
	return s;
}



