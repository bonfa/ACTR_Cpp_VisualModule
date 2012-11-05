#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "TriangleTest.h"
#include "StraightLineTest.h"

void runTest(){
	cute::ide_listener lis;
	//cute::suite s=make_suite_DefaultSuiteName();
	cute::suite straightLineSuite = make_suite_StraightLineTest();
	cute::makeRunner(lis)(straightLineSuite, "StraighLineTest");
	//cute::makeRunner(lis)(s, "The Suite");
}



int main(){
    runTest();
}



