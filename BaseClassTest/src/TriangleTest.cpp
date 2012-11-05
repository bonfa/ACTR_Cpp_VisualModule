#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "TriangleTest.h"


void TriangleTest01(){
	int ax = 0;
	int ay = 0;
	int bx = 2;
	int by = 0;
	int cx = 2;
	int cy = 2;


	string actualChunkString = "cianc, traingle\n";
	Triangle *q = new Triangle(ax,ay,bx,by,cx,cy);
	string realChunkString = q->getChunk();
	ASSERT_EQUAL(actualChunkString,realChunkString);
}



cute::suite make_suite_TriangleTest(){
	cute::suite s;
	s.push_back(CUTE(TriangleTest01));
	return s;
}



