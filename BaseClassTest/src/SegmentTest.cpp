#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "SegmentTest.h"

//TODO: tests
void thisIsASegmentTestTest() {
	ASSERTM("start writing tests", true);
}

cute::suite make_suite_SegmentTest(){
	cute::suite s;
	s.push_back(CUTE(thisIsASegmentTestTest));
	return s;
}



