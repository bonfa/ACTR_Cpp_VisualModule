#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "ObjectTest.h"

//TODO: test for object class (it could be not necessary because it should have never been called directly
void ObjectTest01(){
	;
}


cute::suite make_suite_ObjectTest(){
	cute::suite s;
	s.push_back(CUTE(ObjectTest01));
	return s;
}



