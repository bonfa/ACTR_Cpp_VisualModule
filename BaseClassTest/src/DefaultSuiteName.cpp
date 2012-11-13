#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "DefaultSuiteName.h"

void thisIsADefaultSuiteNameTest() {
	ASSERTM("start writing tests", false);	
}

cute::suite make_suite_DefaultSuiteName(){
	cute::suite s;
	s.push_back(CUTE(thisIsADefaultSuiteNameTest));
	return s;
}



