#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "StraightLineTest.h"


struct TestParameters_01{

	TestParameters_01(): l(1,1,0){
		actualA = 1;
		actualB = 1;
		actualC = 0;
		actualSlope = -1;
		actualIntercept = 0;
		actualIsVertical = false;
	}

	void getterATest_01(){
		double a = l.getA();
		ASSERT_EQUAL(a, actualA);
	}

	void getterBTest_01(){
		double b = l.getB();
		ASSERT_EQUAL(b, actualB);
	}

	void getterCTest_01(){
		double c = l.getC();
		ASSERT_EQUAL(c, actualC);
	}

	void getterSlopeTest_01(){
		double slope = l.getSlope();
		ASSERT_EQUAL(slope,actualSlope);
	}

	void getterInterceptTest_01(){
		double interc = l.getIntercept();
		ASSERT_EQUAL(interc,actualIntercept);
	}

	void verticalTest_01(){
		ASSERT_EQUAL(l.isVertical(), actualIsVertical);
	}

	void pointBelongingTest_01(){
		ASSERT_EQUAL(true,l.doesPointBelongTo(0,0));
	}

	void pointNotBelongingTest_01(){
		ASSERT_EQUAL(false,l.doesPointBelongTo(1,1));
	}

	void getYTest_01(){
		double realY = -5;
		ASSERT_EQUAL(realY,l.getY(5));
	}

	void getInterceptionPointTestWithParallelTest_01(){
		StraightLine secondLine = StraightLine(Point(0,1),Point(1,0));
		ASSERT_THROWS(l.getInterceptionPoint(secondLine),ParallelLinesException);
	}

	void getInterceptionPointTestWithSameTest_01(){
		StraightLine secondLine = StraightLine(Point(0,0),Point(-1,1));
		ASSERT_THROWS(l.getInterceptionPoint(secondLine),CoincidentLinesException);
	}

	void getInterceptionPointTestNoError_A_Test_01(){
		StraightLine secondLine = StraightLine(Point(0,-5),Point(-5,-5));
		ASSERT_EQUAL(l.getInterceptionPoint(secondLine),Point(5,-5));
	}

	void getInterceptionPointTestNoError_B_Test_01(){
		StraightLine secondLine = StraightLine(Point(-1,-1),Point(1,1));
		ASSERT_EQUAL(l.getInterceptionPoint(secondLine),Point(0,0));
	}


	StraightLine l;
	double actualA;
	double actualB;
	double actualC;
	double actualSlope;
	double actualIntercept;
	bool actualIsVertical;

};


struct TestParameters_02{

	TestParameters_02(): l(1,0,5){
		 actualA = 1;
		 actualB = 0;
		 actualC = 5;
		 actualSlope = 0;
		 actualIntercept = -actualC;
		 actualIsVertical = false;
	}

	void getterATest_02(){
		double a = l.getA();
		ASSERT_EQUAL(a, actualA);
	}

	void getterBTest_02(){
		double b = l.getB();
		ASSERT_EQUAL(b, actualB);
	}

	void getterCTest_02(){
		double c = l.getC();
		ASSERT_EQUAL(c, actualC);
	}

	void getterSlopeTest_02(){
		double slope = l.getSlope();
		ASSERT_EQUAL(slope,actualSlope);
	}

	void getterInterceptTest_02(){
		double interc = l.getIntercept();
		ASSERT_EQUAL(interc,actualIntercept);
	}

	void verticalTest_02(){
		ASSERT_EQUAL(l.isVertical(), actualIsVertical);
	}

	void pointBelongingTest_02(){
		ASSERT_EQUAL(true,l.doesPointBelongTo(0,-5));
	}

	void pointNotBelongingTest_02(){
		ASSERT_EQUAL(false,l.doesPointBelongTo(1,1));
	}

	void getYTest_02(){
			double realY = -5;
			ASSERT_EQUAL(realY,l.getY(3));
	}


	void getInterceptionPointTestWithParallelTest_02(){
		StraightLine secondLine = StraightLine(Point(0,0),Point(5,0));
		ASSERT_THROWS(l.getInterceptionPoint(secondLine),ParallelLinesException);
	}

	void getInterceptionPointTestWithSameTest_02(){
		StraightLine secondLine = StraightLine(Point(0,-5),Point(-5,-5));
		ASSERT_THROWS(l.getInterceptionPoint(secondLine),CoincidentLinesException);
	}

	void getInterceptionPointTestNoError_A_Test_02(){
		StraightLine secondLine = StraightLine(Point(-1,-1),Point(1,1));
		ASSERT_EQUAL(l.getInterceptionPoint(secondLine),Point(-5,-5));
	}

	void getInterceptionPointTestNoError_B_Test_02(){
		StraightLine secondLine = StraightLine(Point(0,1),Point(1,0));
		ASSERT_EQUAL(l.getInterceptionPoint(secondLine),Point(6,-5));
	}


	StraightLine l;
	double actualA;
	double actualB;
	double actualC;
	double actualSlope;
	double actualIntercept;
	bool actualIsVertical;

};



struct TestParameters_03{

	TestParameters_03(): l(0,1,5){
		 actualA = 0;
		 actualB = 1;
		 actualC = 5;
		 //actualSlope = 0;
		 //actualIntercept = -actualC;
		 actualIsVertical = true;
	}

	void getterATest_03(){
		double a = l.getA();
		ASSERT_EQUAL(a, actualA);
	}

	void getterBTest_03(){
		double b = l.getB();
		ASSERT_EQUAL(b, actualB);
	}

	void getterCTest_03(){
		double c = l.getC();
		ASSERT_EQUAL(c, actualC);
	}

	void getterSlopeTest_03(){
		ASSERT_THROWS(l.getSlope(),VerticalLineException);
	}

	void getterInterceptTest_03(){
		ASSERT_THROWS(l.getIntercept(), VerticalLineException);
	}

	void verticalTest_03(){
		ASSERT_EQUAL(l.isVertical(), actualIsVertical);
	}

	void pointBelongingTest_03(){
		ASSERT_EQUAL(true,l.doesPointBelongTo(-5,0));
	}

	void pointNotBelongingTest_03(){
		ASSERT_EQUAL(false,l.doesPointBelongTo(1,1));
	}

	void getYTest_03(){
		ASSERT_THROWS(l.getY(3), VerticalLineException);
	}

	void getInterceptionPointTestWithParallelTest_03(){
		StraightLine secondLine = StraightLine(Point(0,0),Point(0,-5));
		ASSERT_THROWS(l.getInterceptionPoint(secondLine),ParallelLinesException);
	}

	void getInterceptionPointTestWithSameTest_03(){
		StraightLine secondLine = StraightLine(Point(-5,0),Point(-5,-5));
		ASSERT_THROWS(l.getInterceptionPoint(secondLine),CoincidentLinesException);
	}

	void getInterceptionPointTestNoError_A_Test_03(){
		StraightLine secondLine = StraightLine(Point(-1,-1),Point(1,1));
		ASSERT_EQUAL(l.getInterceptionPoint(secondLine),Point(-5,-5));
	}

	void getInterceptionPointTestNoError_B_Test_03(){
		StraightLine secondLine = StraightLine(Point(0,1),Point(1,0));
		ASSERT_EQUAL(l.getInterceptionPoint(secondLine),Point(-5,6));
	}

	StraightLine l;
	double actualA;
	double actualB;
	double actualC;
	//double actualSlope;
	//double actualIntercept;
	bool actualIsVertical;

};



struct TestParameters_04{
	TestParameters_04(): l(1,1,-1,-1){
		 actualA = -2;
		 actualB = 2;
		 actualC = 0;
		 actualSlope = 1;
		 actualIntercept = 0;
		 actualIsVertical = false;
		}

		void getterATest_04(){
			double a = l.getA();
			ASSERT_EQUAL(a, actualA);
		}

		void getterBTest_04(){
			double b = l.getB();
			ASSERT_EQUAL(b, actualB);
		}

		void getterCTest_04(){
			double c = l.getC();
			ASSERT_EQUAL(c, actualC);
		}

		void getterSlopeTest_04(){
			double slope = l.getSlope();
			ASSERT_EQUAL(slope,actualSlope);
		}

		void getterInterceptTest_04(){
			double interc = l.getIntercept();
			ASSERT_EQUAL(interc,actualIntercept);
		}

		void verticalTest_04(){
			ASSERT_EQUAL(l.isVertical(), actualIsVertical);
		}

		void pointBelongingTest_04(){
			ASSERT_EQUAL(true,l.doesPointBelongTo(0,0));
		}

		void pointNotBelongingTest_04(){
			ASSERT_EQUAL(false,l.doesPointBelongTo(1,2));
		}

		void getYTest_04(){
			double realY = 5;
			ASSERT_EQUAL(realY,l.getY(5));
		}


		StraightLine l;
		double actualA;
		double actualB;
		double actualC;
		double actualSlope;
		double actualIntercept;
		bool actualIsVertical;

};




struct TestParameters_05{
	TestParameters_05(): l(0,5,5,5){
		 actualA = 5;
		 actualB = 0;
		 actualC = -25;
		 actualSlope = 0;
		 actualIntercept = 5;
		 actualIsVertical = false;
		}

			void getterATest_05(){
				double a = l.getA();
				ASSERT_EQUAL(a, actualA);
			}

			void getterBTest_05(){
				double b = l.getB();
				ASSERT_EQUAL(b, actualB);
			}

			void getterCTest_05(){
				double c = l.getC();
				ASSERT_EQUAL(c, actualC);
			}

			void getterSlopeTest_05(){
				double slope = l.getSlope();
				ASSERT_EQUAL(slope,actualSlope);
			}

			void getterInterceptTest_05(){
				double interc = l.getIntercept();
				ASSERT_EQUAL(interc,actualIntercept);
			}

			void verticalTest_05(){
				ASSERT_EQUAL(l.isVertical(), actualIsVertical);
			}

			void pointBelongingTest_05(){
				ASSERT_EQUAL(true,l.doesPointBelongTo(1,5));
			}

			void pointNotBelongingTest_05(){
				ASSERT_EQUAL(false,l.doesPointBelongTo(0,0));
			}

			void getYTest_05(){
				double realY = 5;
				ASSERT_EQUAL(realY,l.getY(2));
			}


			StraightLine l;
			double actualA;
			double actualB;
			double actualC;
			double actualSlope;
			double actualIntercept;
			bool actualIsVertical;
};



struct TestParameters_06{
	TestParameters_06(): l(5,0,5,5){
		 actualA = 0;
		 actualB = 1;
		 actualC = -5;

		 actualIsVertical = true;
		}

			void getterATest_06(){
				double a = l.getA();
				ASSERT_EQUAL(a, actualA);
			}

			void getterBTest_06(){
				double b = l.getB();
				ASSERT_EQUAL(b, actualB);
			}

			void getterCTest_06(){
				double c = l.getC();
				ASSERT_EQUAL(c, actualC);
			}

			void getterSlopeTest_06(){
				ASSERT_THROWS(l.getSlope(),VerticalLineException);
			}

			void getterInterceptTest_06(){
				ASSERT_THROWS(l.getIntercept(), VerticalLineException);
			}

			void verticalTest_06(){
				ASSERT_EQUAL(l.isVertical(), actualIsVertical);
			}

			void pointBelongingTest_06(){
				ASSERT_EQUAL(true,l.doesPointBelongTo(5,1));
			}

			void pointNotBelongingTest_06(){
				ASSERT_EQUAL(false,l.doesPointBelongTo(0,0));
			}

			void getYTest_06(){
				ASSERT_THROWS(l.getY(3), VerticalLineException);
			}


			StraightLine l;
			double actualA;
			double actualB;
			double actualC;
			bool actualIsVertical;
};


void StraightLineTestSecondConstructor04(){
	int xa = 5, ya = 5;
	int xb = 5, yb = 5;

	ASSERT_THROWS(StraightLine(xa,ya,xb,yb),InputException);

}


cute::suite make_suite_StraightLineTest(){
	cute::suite s;
	s+= CUTE_SMEMFUN(TestParameters_01,getterATest_01);
	s+= CUTE_SMEMFUN(TestParameters_02,getterATest_02);
	s+= CUTE_SMEMFUN(TestParameters_03,getterATest_03);
	s+= CUTE_SMEMFUN(TestParameters_04,getterATest_04);
	s+= CUTE_SMEMFUN(TestParameters_05,getterATest_05);
	s+= CUTE_SMEMFUN(TestParameters_06,getterATest_06);

	s+= CUTE_SMEMFUN(TestParameters_01,getterBTest_01);
	s+= CUTE_SMEMFUN(TestParameters_02,getterBTest_02);
	s+= CUTE_SMEMFUN(TestParameters_03,getterBTest_03);
	s+= CUTE_SMEMFUN(TestParameters_04,getterBTest_04);
	s+= CUTE_SMEMFUN(TestParameters_05,getterBTest_05);
	s+= CUTE_SMEMFUN(TestParameters_06,getterBTest_06);

	s+= CUTE_SMEMFUN(TestParameters_01,getterCTest_01);
	s+= CUTE_SMEMFUN(TestParameters_02,getterCTest_02);
	s+= CUTE_SMEMFUN(TestParameters_03,getterCTest_03);
	s+= CUTE_SMEMFUN(TestParameters_04,getterCTest_04);
	s+= CUTE_SMEMFUN(TestParameters_05,getterCTest_05);
	s+= CUTE_SMEMFUN(TestParameters_06,getterCTest_06);

	s+= CUTE_SMEMFUN(TestParameters_01,getterSlopeTest_01);
	s+= CUTE_SMEMFUN(TestParameters_02,getterSlopeTest_02);
	s+= CUTE_SMEMFUN(TestParameters_03,getterSlopeTest_03);
	s+= CUTE_SMEMFUN(TestParameters_04,getterSlopeTest_04);
	s+= CUTE_SMEMFUN(TestParameters_05,getterSlopeTest_05);
	s+= CUTE_SMEMFUN(TestParameters_06,getterSlopeTest_06);

	s+= CUTE_SMEMFUN(TestParameters_01,getterInterceptTest_01);
	s+= CUTE_SMEMFUN(TestParameters_02,getterInterceptTest_02);
	s+= CUTE_SMEMFUN(TestParameters_03,getterInterceptTest_03);
	s+= CUTE_SMEMFUN(TestParameters_04,getterInterceptTest_04);
	s+= CUTE_SMEMFUN(TestParameters_05,getterInterceptTest_05);
	s+= CUTE_SMEMFUN(TestParameters_06,getterInterceptTest_06);

	s+= CUTE_SMEMFUN(TestParameters_01,verticalTest_01);
	s+= CUTE_SMEMFUN(TestParameters_02,verticalTest_02);
	s+= CUTE_SMEMFUN(TestParameters_03,verticalTest_03);
	s+= CUTE_SMEMFUN(TestParameters_04,verticalTest_04);
	s+= CUTE_SMEMFUN(TestParameters_05,verticalTest_05);
	s+= CUTE_SMEMFUN(TestParameters_06,verticalTest_06);


	s+= CUTE_SMEMFUN(TestParameters_01,pointBelongingTest_01);
	s+= CUTE_SMEMFUN(TestParameters_02,pointBelongingTest_02);
	s+= CUTE_SMEMFUN(TestParameters_03,pointBelongingTest_03);
	s+= CUTE_SMEMFUN(TestParameters_04,pointBelongingTest_04);
	s+= CUTE_SMEMFUN(TestParameters_05,pointBelongingTest_05);
	s+= CUTE_SMEMFUN(TestParameters_06,pointBelongingTest_06);

	s+= CUTE_SMEMFUN(TestParameters_01,pointNotBelongingTest_01);
	s+= CUTE_SMEMFUN(TestParameters_02,pointNotBelongingTest_02);
	s+= CUTE_SMEMFUN(TestParameters_03,pointNotBelongingTest_03);
	s+= CUTE_SMEMFUN(TestParameters_04,pointNotBelongingTest_04);
	s+= CUTE_SMEMFUN(TestParameters_05,pointNotBelongingTest_05);
	s+= CUTE_SMEMFUN(TestParameters_06,pointNotBelongingTest_06);

	s+= CUTE_SMEMFUN(TestParameters_01,getYTest_01);
	s+= CUTE_SMEMFUN(TestParameters_02,getYTest_02);
	s+= CUTE_SMEMFUN(TestParameters_03,getYTest_03);
	s+= CUTE_SMEMFUN(TestParameters_04,getYTest_04);
	s+= CUTE_SMEMFUN(TestParameters_05,getYTest_05);
	s+= CUTE_SMEMFUN(TestParameters_06,getYTest_06);

	s+= CUTE_SMEMFUN(TestParameters_01,getInterceptionPointTestWithParallelTest_01);
	s+= CUTE_SMEMFUN(TestParameters_01,getInterceptionPointTestWithSameTest_01);
	s+= CUTE_SMEMFUN(TestParameters_01,getInterceptionPointTestNoError_A_Test_01);
	s+= CUTE_SMEMFUN(TestParameters_01,getInterceptionPointTestNoError_B_Test_01);
	s+= CUTE_SMEMFUN(TestParameters_02,getInterceptionPointTestWithParallelTest_02);
	s+= CUTE_SMEMFUN(TestParameters_02,getInterceptionPointTestWithSameTest_02);
	s+= CUTE_SMEMFUN(TestParameters_02,getInterceptionPointTestNoError_A_Test_02);
	s+= CUTE_SMEMFUN(TestParameters_02,getInterceptionPointTestNoError_B_Test_02);
	s+= CUTE_SMEMFUN(TestParameters_03,getInterceptionPointTestWithParallelTest_03);
	s+= CUTE_SMEMFUN(TestParameters_03,getInterceptionPointTestWithSameTest_03);
	s+= CUTE_SMEMFUN(TestParameters_03,getInterceptionPointTestNoError_A_Test_03);
	s+= CUTE_SMEMFUN(TestParameters_03,getInterceptionPointTestNoError_B_Test_03);



	s.push_back(CUTE(StraightLineTestSecondConstructor04));
	return s;
}



