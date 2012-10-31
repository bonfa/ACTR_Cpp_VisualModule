#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "TriangleTest.h"

void thisIsADefaultSuiteNameTest() {
	ASSERTM("start writing tests", true);
}



cute::suite make_suite_DefaultSuiteName(){
	cute::suite s;
	s.push_back(CUTE(thisIsADefaultSuiteNameTest));
	return s;
}



