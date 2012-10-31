#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "BaseClassTest.h"

void thisIsABaseClassTestTest() {
	ASSERTM("start writing tests", false);	
}

cute::suite make_suite_BaseClassTest(){
	cute::suite s;
	s.push_back(CUTE(thisIsABaseClassTestTest));
	return s;
}



