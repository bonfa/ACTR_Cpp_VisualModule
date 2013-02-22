#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "CircleTest.h"


struct ConstructorError{
	void CircleTest_Errors_01(){
		int ax = -1;
		int ay = 6;
		int radius = 3;

		ASSERT_THROWS(new Circle(radius,ax,ay,""),InputException);
	}


	void CircleTest_Errors_02(){
		int ax = 1;
		int ay = -6;
		int radius = 3;

		ASSERT_THROWS(new Circle(radius,ax,ay,""),InputException);
	}


	void CircleTest_Errors_03(){
		int ax = 5;
		int ay = 6;
		int radius = -3;

		ASSERT_THROWS(new Circle(radius,ax,ay,""),InputException);
	}
};

struct CircleTest_01{

	CircleTest_01(): c(3,5,5,""){
		expectedAx = 5;
		expectedAy = 5;
		expectedRadius = 3;
		expectedChunkString = "cianc, Circle\n";
		expectedCenter = Point(expectedAx,expectedAy);
		expectedRotation = 0;
	}


	void constructorCheck(){
		ASSERT(&c!=NULL);
	}


	void getXCenterCheck(){
		ASSERT_EQUAL(expectedAx,c.getXCenter());
	}


	void getYCenterCheck(){
		ASSERT_EQUAL(expectedAy,c.getYCenter());
	}


	void getRadiusCheck(){
		ASSERT_EQUAL(expectedRadius,c.getRadius());
	}

	void getChunkCheck(){
		ASSERT_EQUAL(expectedChunkString,c.getChunk());
	}

	void getCenterCheck(){
		ASSERT_EQUAL(expectedCenter,c.getCenter());
	}

	void getRotationCheck(){
		ASSERT_EQUAL(expectedRotation,c.getRotation());
	}

	Circle c;
	int expectedAx;
	int expectedAy;
	int expectedRadius;
	string expectedChunkString;
	Point expectedCenter;
	double expectedRotation;
};



struct CircleTest_02{

	CircleTest_02(): c(3,5,6,""){
		expectedAx = 5;
		expectedAy = 6;
		expectedRadius = 3;
		expectedChunkString = "cianc, Circle\n";
		expectedCenter = Point(expectedAx,expectedAy);
		expectedRotation = 0;
	}


	void constructorCheck(){
		ASSERT(&c!=NULL);
	}


	void getXCenterCheck(){
		ASSERT_EQUAL(expectedAx,c.getXCenter());
	}


	void getYCenterCheck(){
		ASSERT_EQUAL(expectedAy,c.getYCenter());
	}


	void getRadiusCheck(){
		ASSERT_EQUAL(expectedRadius,c.getRadius());
	}

	void getChunkCheck(){
		ASSERT_EQUAL(expectedChunkString,c.getChunk());
	}

	void getCenterCheck(){
		ASSERT_EQUAL(expectedCenter,c.getCenter());
	}

	void getRotationCheck(){
		ASSERT_EQUAL(expectedRotation,c.getRotation());
	}

	Circle c;
	int expectedAx;
	int expectedAy;
	int expectedRadius;
	string expectedChunkString;
	Point expectedCenter;
	double expectedRotation;
};




cute::suite make_suite_CircleTest(){
	cute::suite s;

	s+= CUTE_SMEMFUN(CircleTest_01,constructorCheck);
	s+= CUTE_SMEMFUN(CircleTest_01,getXCenterCheck);
	s+= CUTE_SMEMFUN(CircleTest_01,getYCenterCheck);
	s+= CUTE_SMEMFUN(CircleTest_01,getRadiusCheck);
	s+= CUTE_SMEMFUN(CircleTest_01,getChunkCheck);
	s+= CUTE_SMEMFUN(CircleTest_01,getCenterCheck);
	s+= CUTE_SMEMFUN(CircleTest_01,getRotationCheck);

	s+= CUTE_SMEMFUN(CircleTest_02,constructorCheck);
	s+= CUTE_SMEMFUN(CircleTest_02,getXCenterCheck);
	s+= CUTE_SMEMFUN(CircleTest_02,getYCenterCheck);
	s+= CUTE_SMEMFUN(CircleTest_02,getRadiusCheck);
	s+= CUTE_SMEMFUN(CircleTest_02,getChunkCheck);
	s+= CUTE_SMEMFUN(CircleTest_02,getCenterCheck);
	s+= CUTE_SMEMFUN(CircleTest_02,getRotationCheck);

	s+= CUTE_SMEMFUN(ConstructorError,CircleTest_Errors_01);
	s+= CUTE_SMEMFUN(ConstructorError,CircleTest_Errors_02);
	s+= CUTE_SMEMFUN(ConstructorError,CircleTest_Errors_03);
	return s;
}



