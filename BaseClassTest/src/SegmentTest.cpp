#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "SegmentTest.h"

void thisIsASegmentTestTest() {
	ASSERTM("start writing tests", false);	
}

cute::suite make_suite_SegmentTest(){
	cute::suite s;
	s.push_back(CUTE(thisIsASegmentTestTest));
	return s;
}



