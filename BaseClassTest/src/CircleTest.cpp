#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "CircleTest.h"

void thisIsACircleTestTest() {
	ASSERTM("start writing tests", false);	
}

cute::suite make_suite_CircleTest(){
	cute::suite s;
	s.push_back(CUTE(thisIsACircleTestTest));
	return s;
}



