#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "QuadrilateralTest.h"

void thisIsAQuadrilateralTestTest() {
	ASSERTM("start writing tests", false);	
}

cute::suite make_suite_QuadrilateralTest(){
	cute::suite s;
	s.push_back(CUTE(thisIsAQuadrilateralTestTest));
	return s;
}



