#define ASSERT_UNEQUAL(expected, actual) ASSERT_OP(expected, actual, !=)

#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "TriangleTest.h"
#include "StraightLineTest.h"
#include "QuadrilateralTest.h"
#include "TriangleTest.h"
#include "ObjectTest.h"
#include "CircleTest.h"
#include "ButtonTest.h"
#include "BlobTest.h"
#include "utilsTest.h"
#include "extractorUtilsTest.h"
#include "SegmentTest.h"

#include "QRScannerTest.h"

#include "MyPointTest.h"
#include "RectTest.h"
#include "InputTest.h"


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

	cute::suite buttonTest = make_suite_ButtonTest();
	cute::makeRunner(lis)(buttonTest, "ButtonTest");

	cute::suite blobTest = make_suite_BlobTest();
	cute::makeRunner(lis)(blobTest, "BlobTest");

	cute::suite utilsTest = make_suite_utilsTest();
	cute::makeRunner(lis)(utilsTest, "utilsTest");


	cute::suite QRScannerTest = make_suite_QRScannerTest();
	cute::makeRunner(lis)(QRScannerTest, "QRScannerTest");


	cute::suite PointTest = make_suite_MyPointTest();
	cute::makeRunner(lis)(PointTest, "PointTest");

	cute::suite RectTest = make_suite_RectTest();
	cute::makeRunner(lis)(RectTest, "RectTest");

	cute::suite extractorUtilsTest = make_suite_extractorUtilsTest();
	cute::makeRunner(lis)(extractorUtilsTest, "extractorUtilsTest");

	cute::suite segmentTest = make_suite_SegmentTest();
	cute::makeRunner(lis)(segmentTest, "RectTest");

	cute::suite inputTest = make_suite_InputTest();
	cute::makeRunner(lis)(inputTest, "InputTest");

}



int main(){
    runTest();
}



