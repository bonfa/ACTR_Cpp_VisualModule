#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "ButtonTest.h"

void thisIsAButtonTestTest() {
	ASSERTM("start writing tests", false);	
}

cute::suite make_suite_ButtonTest(){
	cute::suite s;
	s.push_back(CUTE(thisIsAButtonTestTest));
	return s;
}



