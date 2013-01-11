#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "MyPointTest.h"


struct PointTest_01{

	PointTest_01(): p(){}

	void Constructor(){
		ASSERT(&p != NULL);
	}

	void checkX(){
		ASSERT_EQUAL(0,p.x);
	}

	void checkY(){
		ASSERT_EQUAL(0,p.y);
	}

	void checkEqual_01(){
		Point *p2 = new Point();
		ASSERT_EQUAL(*p2,p);
	}

	void checkEqual_02(){
		Point *p2 = new Point(0,0);
		ASSERT_EQUAL(*p2,p);
	}

	void checkEqual_03(){
		Point p2(0,4);
		ASSERT_EQUAL(false,p2==p);
	}

	void checkEqual_04(){
		Point p2(-5,0);
		ASSERT_EQUAL(false,p2==p);
	}

	Point p;
};


struct PointTest_02{

	PointTest_02(): p(4,5){}

	void Constructor(){
		ASSERT(&p != NULL);
	}

	void checkX(){
		ASSERT_EQUAL(4,p.x);
	}

	void checkY(){
		ASSERT_EQUAL(5,p.y);
	}

	void checkEqual_01(){
		Point *p2 = new Point(4,5);
		ASSERT_EQUAL(*p2,p);
	}

	void checkEqual_02(){
		Point p2(0,0);
		ASSERT_EQUAL(false,p2==p);
	}

	void checkEqual_03(){
		Point p2(4,4);
		ASSERT_EQUAL(false,p2==p);
	}

	void checkEqual_04(){
		Point p2(-5,5);
		ASSERT_EQUAL(false,p2==p);
	}

	Point p;
};



struct PointTest_03{

	PointTest_03(): p(-5,-4){}

	void Constructor(){
		ASSERT(&p != NULL);
	}

	void checkX(){
		ASSERT_EQUAL(-5,p.x);
	}

	void checkY(){
		ASSERT_EQUAL(-4,p.y);
	}

	void checkEqual_01(){
		Point *p2 = new Point(-5,-4);
		ASSERT_EQUAL(*p2,p);
	}

	void checkEqual_02(){
		Point p2(5,4);
		ASSERT_EQUAL(false,p2==p);
	}

	void checkEqual_03(){
		Point p2(-5,4);
		ASSERT_EQUAL(false,p2==p);
	}

	void checkEqual_04(){
		Point p2(-5,10);
		ASSERT_EQUAL(false,p2==p);
	}


	void checkEqual_05(){
		Point p2(5,-4);
		ASSERT_EQUAL(false,p2==p);
	}


	Point p;
};



cute::suite make_suite_MyPointTest(){
	cute::suite s;

	s+= CUTE_SMEMFUN(PointTest_01,Constructor);
	s+= CUTE_SMEMFUN(PointTest_01,checkX);
	s+= CUTE_SMEMFUN(PointTest_01,checkY);
	s+= CUTE_SMEMFUN(PointTest_01,checkEqual_01);
	s+= CUTE_SMEMFUN(PointTest_01,checkEqual_02);
	s+= CUTE_SMEMFUN(PointTest_01,checkEqual_03);
	s+= CUTE_SMEMFUN(PointTest_01,checkEqual_04);

	s+= CUTE_SMEMFUN(PointTest_02,Constructor);
	s+= CUTE_SMEMFUN(PointTest_02,checkX);
	s+= CUTE_SMEMFUN(PointTest_02,checkY);
	s+= CUTE_SMEMFUN(PointTest_02,checkEqual_01);
	s+= CUTE_SMEMFUN(PointTest_02,checkEqual_02);
	s+= CUTE_SMEMFUN(PointTest_02,checkEqual_03);
	s+= CUTE_SMEMFUN(PointTest_02,checkEqual_04);

	s+= CUTE_SMEMFUN(PointTest_03,Constructor);
	s+= CUTE_SMEMFUN(PointTest_03,checkX);
	s+= CUTE_SMEMFUN(PointTest_03,checkY);
	s+= CUTE_SMEMFUN(PointTest_03,checkEqual_01);
	s+= CUTE_SMEMFUN(PointTest_03,checkEqual_02);
	s+= CUTE_SMEMFUN(PointTest_03,checkEqual_03);
	s+= CUTE_SMEMFUN(PointTest_03,checkEqual_04);
	s+= CUTE_SMEMFUN(PointTest_03,checkEqual_05);

	return s;
}



