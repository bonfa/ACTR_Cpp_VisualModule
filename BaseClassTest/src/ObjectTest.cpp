#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "ObjectTest.h"

void thisIsAObjectTestTest() {
	ASSERTM("start writing tests", false);	
}

cute::suite make_suite_ObjectTest(){
	cute::suite s;
	s.push_back(CUTE(thisIsAObjectTestTest));
	return s;
}



