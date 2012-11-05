#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "CircleTest.h"

void CircleTest01(){
	int ax = 5;
	int ay = 5;
	int radius = 3;

	string actualChunkString = "cianc, Circle\n";
	Circle *q = new Circle(radius,ax,ay);
	string realChunkString = q->getChunk();
	ASSERT_EQUAL(actualChunkString,realChunkString);
}

cute::suite make_suite_CircleTest(){
	cute::suite s;
	s.push_back(CUTE(CircleTest01));
	return s;
}



