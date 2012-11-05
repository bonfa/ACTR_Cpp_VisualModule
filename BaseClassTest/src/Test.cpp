#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "TriangleTest.h"
#include "StraightLineTest.h"
#include "QuadrilateralTest.h"
#include "TriangleTest.h"
#include "ObjectTest.h"
#include "CircleTest.h"


void runTest(){
	cute::ide_listener lis;

	cute::suite straightLineSuite = make_suite_StraightLineTest();
	cute::makeRunner(lis)(straightLineSuite, "StraighLineTest");

	cute::suite quadrilateralSuite = make_suite_QuadrilateralTest();
	cute::makeRunner(lis)(quadrilateralSuite, "QuadrilateralTest");

	cute::suite triangleSuite = make_suite_TriangleTest();
	cute::makeRunner(lis)(triangleSuite, "TriangleTest");

	cute::suite objectSuite = make_suite_ObjectTest();
	cute::makeRunner(lis)(objectSuite, "ObjectTest");

	cute::suite circleTest = make_suite_CircleTest();
	cute::makeRunner(lis)(circleTest, "CircleTest");
}



int main(){
    runTest();
}



