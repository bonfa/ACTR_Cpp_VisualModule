#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "extractorUtilsTest.h"

//@ATTENTION: Makes no sense testing most of this method because parameters can change.
//Good to check for errors


void myDistanceTest_01() {
	cv::Point p1 = cv::Point(0,0);
	ASSERT_EQUAL(0,myDistance(p1,p1));
}

void myDistanceTest_02() {
	cv::Point p1 = cv::Point(1,4);
	ASSERT_EQUAL(0,myDistance(p1,p1));
}

void myDistanceTest_03() {
	cv::Point p1 = cv::Point(0,4);
	cv::Point p2 = cv::Point(0,2);
	ASSERT_EQUAL(2,myDistance(p1,p2));
}


void myDistanceTest_04() {
	cv::Point p1 = cv::Point(4,0);
	cv::Point p2 = cv::Point(2,0);
	ASSERT_EQUAL(2,myDistance(p1,p2));
}


void myDistanceTest_05() {
	cv::Point p1 = cv::Point(-4,0);
	cv::Point p2 = cv::Point(-2,0);
	ASSERT_EQUAL(2,myDistance(p1,p2));
}


void myDistanceTest_06() {
	cv::Point p1 = cv::Point(0,0);
	cv::Point p2 = cv::Point(3,4);
	ASSERT_EQUAL(5,myDistance(p1,p2));
}

void myDistanceTest_07() {
	cv::Point p1 = cv::Point(0,0);
	cv::Point p2;  //default a (0,0)
	ASSERT_EQUAL(0,myDistance(p1,p2));
}


void tooCloseTest_01(){
	cv::Point p1 = cv::Point(0,0);
	cv::Point p2 = cv::Point(2,2);
	bool tc = tooClose(p1,p2);
	ASSERT_EQUAL(true,tc);
}


void tooCloseTest_02(){
	cv::Point p1 = cv::Point(0,0);
	cv::Point p2 = cv::Point(0,15);
	ASSERT_EQUAL(false,tooClose(p1,p2));
}

void tooCloseTest_03(){
	cv::Point p1 = cv::Point(15,0);
	cv::Point p2 = cv::Point(0,15);
	ASSERT_EQUAL(false,tooClose(p1,p2));
}


void isFalseTest_01(){
	cv::vector<cv::Point> square;
	square.push_back(cv::Point(0,0));
	square.push_back(cv::Point(0,15));
	square.push_back(cv::Point(20,15));
	square.push_back(cv::Point(20,0));
	ASSERT_EQUAL(false,isFalse(square));
}


void isFalseTest_02(){
	cv::vector<cv::Point> square;
	square.push_back(cv::Point(0,0));
	square.push_back(cv::Point(0,1));
	square.push_back(cv::Point(2,1));
	square.push_back(cv::Point(2,2));
	ASSERT_EQUAL(true,isFalse(square));
}


void isTriangleTest_01(){
	cv::vector<cv::Point> square;
	square.push_back(cv::Point(0,0));
	square.push_back(cv::Point(0,1));
	square.push_back(cv::Point(2,1));
	ASSERT_EQUAL(false,isTriangle(square));
}


void isTriangleTest_02(){
	cv::vector<cv::Point> square;
	square.push_back(cv::Point(0,100));
	square.push_back(cv::Point(100,100));
	square.push_back(cv::Point(200,300));
	ASSERT_EQUAL(true,isTriangle(square));
}


void similar_01(){
	cv::vector<cv::Point> a;
	a.push_back(cv::Point(0,0));
	a.push_back(cv::Point(100,100));
	a.push_back(cv::Point(200,200));

	cv::vector<cv::Point> b;
	b.push_back(cv::Point(1,1));
	b.push_back(cv::Point(101,101));
	b.push_back(cv::Point(201,201));

	ASSERT_EQUAL(true,similar(a,b));
}


void similar_02(){
	cv::vector<cv::Point> a;
	a.push_back(cv::Point(0,0));
	a.push_back(cv::Point(100,100));
	a.push_back(cv::Point(200,200));

	cv::vector<cv::Point> b;
	b.push_back(cv::Point(1010,1010));
	b.push_back(cv::Point(201,201));
	b.push_back(cv::Point(1,1));

	ASSERT_EQUAL(false,similar(a,b));
}


void similar_03(){
	cv::vector<cv::Point> a;
	a.push_back(cv::Point(0,0));
	a.push_back(cv::Point(100,100));
	a.push_back(cv::Point(200,200));

	cv::vector<cv::Point> b;
	b.push_back(cv::Point(1,1));
	b.push_back(cv::Point(101,101));
	b.push_back(cv::Point(201,201));
	b.push_back(cv::Point(201,201));

	ASSERT_EQUAL(false,similar(a,b));
}



void similar_04(){
	cv::vector<cv::Point> a;
	a.push_back(cv::Point(0,0));
	a.push_back(cv::Point(100,100));
	a.push_back(cv::Point(200,200));

	cv::vector<cv::Point> b;
	b.push_back(cv::Point(501,501));
	b.push_back(cv::Point(201,301));
	b.push_back(cv::Point(1,1));

	ASSERT_EQUAL(false,similar(a,b));
}


void deleteFalseSquaresTest_01(){
	cv::vector<cv::vector<cv::Point> > inputList;
	cv::vector<cv::vector<cv::Point> > expectedOutputList;

	cv::vector<cv::vector<cv::Point> > b = deleteFalseSquares(inputList);
	ASSERT_EQUAL(expectedOutputList,b);
}


void deleteFalseSquaresTest_02(){
	cv::vector<cv::vector<cv::Point> > inputList;
	cv::vector<cv::vector<cv::Point> > expectedOutputList;

	cv::vector<cv::Point> q1;
	q1.push_back(cv::Point(0,0));
	q1.push_back(cv::Point(0,100));
	q1.push_back(cv::Point(200,0));
	q1.push_back(cv::Point(200,100));

	cv::vector<cv::Point> q2;
	q2.push_back(cv::Point(0,0));
	q2.push_back(cv::Point(0,1));
	q2.push_back(cv::Point(200,0));
	q2.push_back(cv::Point(200,100));

	inputList.push_back(q1);
	inputList.push_back(q2);

	expectedOutputList.push_back(q1);

	cv::vector<cv::vector<cv::Point> > b = deleteFalseSquares(inputList);
	ASSERT_EQUAL(expectedOutputList,b);
}


void deleteFalseSquaresTest_03(){
	cv::vector<cv::vector<cv::Point> > inputList;
	cv::vector<cv::vector<cv::Point> > expectedOutputList;

	cv::vector<cv::Point> q2;
	q2.push_back(cv::Point(0,0));
	q2.push_back(cv::Point(0,1));
	q2.push_back(cv::Point(200,0));
	q2.push_back(cv::Point(200,100));

	inputList.push_back(q2);

	cv::vector<cv::vector<cv::Point> > b = deleteFalseSquares(inputList);
	ASSERT_EQUAL(expectedOutputList,b);
}


void deleteFalseSquaresTest_04(){
	cv::vector<cv::vector<cv::Point> > inputList;
	cv::vector<cv::vector<cv::Point> > expectedOutputList;

	cv::vector<cv::Point> q1;
	q1.push_back(cv::Point(0,0));
	q1.push_back(cv::Point(0,100));
	q1.push_back(cv::Point(200,0));
	q1.push_back(cv::Point(200,100));

	inputList.push_back(q1);
	inputList.push_back(q1);

	expectedOutputList.push_back(q1);
	expectedOutputList.push_back(q1);

	cv::vector<cv::vector<cv::Point> > b = deleteFalseSquares(inputList);
	ASSERT_EQUAL(expectedOutputList,b);
}


void squareSortTest_01(){
	cv::vector<cv::vector<cv::Point> > inputList;
	cv::vector<cv::vector<cv::Point> > expectedOutputList;

	cv::vector<cv::vector<cv::Point> > b = squaresSort(inputList);
	ASSERT_EQUAL(expectedOutputList,b);
}


void squareSortTest_02(){
	cv::vector<cv::vector<cv::Point> > inputList;
	cv::vector<cv::vector<cv::Point> > expectedOutputList;

	cv::vector<cv::Point> q1;
	q1.push_back(cv::Point(0,0));
	q1.push_back(cv::Point(0,100));
	q1.push_back(cv::Point(200,0));
	q1.push_back(cv::Point(200,100));

	cv::vector<cv::Point> q2;
	q2.push_back(cv::Point(0,0));
	q2.push_back(cv::Point(0,1));
	q2.push_back(cv::Point(200,0));
	q2.push_back(cv::Point(200,100));

	inputList.push_back(q1);
	inputList.push_back(q2);

	expectedOutputList.push_back(q1);
	expectedOutputList.push_back(q2);

	cv::vector<cv::vector<cv::Point> > b = squaresSort(inputList);
	ASSERT_EQUAL(expectedOutputList,b);
}


void squareSortTest_03(){
	cv::vector<cv::vector<cv::Point> > inputList;
	cv::vector<cv::vector<cv::Point> > expectedOutputList;

	cv::vector<cv::Point> q1;
	q1.push_back(cv::Point(0,0));
	q1.push_back(cv::Point(0,100));
	q1.push_back(cv::Point(200,0));
	q1.push_back(cv::Point(200,100));

	cv::vector<cv::Point> q2;
	q2.push_back(cv::Point(0,0));
	q2.push_back(cv::Point(0,1));
	q2.push_back(cv::Point(200,0));
	q2.push_back(cv::Point(200,100));

	inputList.push_back(q2);
	inputList.push_back(q1);

	expectedOutputList.push_back(q2);
	expectedOutputList.push_back(q1);

	cv::vector<cv::vector<cv::Point> > b = squaresSort(inputList);
	ASSERT_EQUAL(expectedOutputList,b);
}


void squareSortTest_04(){
	cv::vector<cv::vector<cv::Point> > inputList;
	cv::vector<cv::vector<cv::Point> > expectedOutputList;

	cv::vector<cv::Point> q1;
	q1.push_back(cv::Point(10,10));
	q1.push_back(cv::Point(100,100));
	q1.push_back(cv::Point(200,200));
	q1.push_back(cv::Point(200,100));

	cv::vector<cv::Point> q2;
	q2.push_back(cv::Point(20,20));
	q2.push_back(cv::Point(200,200));
	q2.push_back(cv::Point(200,0));
	q2.push_back(cv::Point(200,100));


	cv::vector<cv::Point> q3;
	q3.push_back(cv::Point(0,20));
	q3.push_back(cv::Point(300,200));
	q3.push_back(cv::Point(500,0));
	q3.push_back(cv::Point(100,100));

	inputList.push_back(q1);
	inputList.push_back(q2);
	inputList.push_back(q3);

	expectedOutputList.push_back(q3);
	expectedOutputList.push_back(q1);
	expectedOutputList.push_back(q2);

	cv::vector<cv::vector<cv::Point> > b = squaresSort(inputList);
	ASSERT_EQUAL(expectedOutputList,b);
}


void deleteOverlappedTest_01(){
	cv::vector<cv::vector<cv::Point> > inputList;
	cv::vector<cv::vector<cv::Point> > expectedOutputList;

	cv::vector<cv::vector<cv::Point> > b = deleteOverlapped(inputList);
	ASSERT_EQUAL(expectedOutputList,b);
}


void deleteOverlappedTest_02(){
	cv::vector<cv::vector<cv::Point> > inputList;
	cv::vector<cv::vector<cv::Point> > expectedOutputList;

	cv::vector<cv::Point> q1;
	q1.push_back(cv::Point(0,0));
	q1.push_back(cv::Point(100,50));
	q1.push_back(cv::Point(200,200));
	q1.push_back(cv::Point(25,300));

	cv::vector<cv::Point> q2;
	q2.push_back(cv::Point(1,1));
	q2.push_back(cv::Point(101,51));
	q2.push_back(cv::Point(200,200));
	q2.push_back(cv::Point(23,301));

	cv::vector<cv::Point> q3;
	q3.push_back(cv::Point(400,400));
	q3.push_back(cv::Point(601,401));
	q3.push_back(cv::Point(800,1000));
	q3.push_back(cv::Point(798,20));

	inputList.push_back(q1);
	inputList.push_back(q2);
	inputList.push_back(q3);

	expectedOutputList.push_back(q1);
	expectedOutputList.push_back(q3);

	cv::vector<cv::vector<cv::Point> > b = deleteOverlapped(inputList);
	ASSERT_EQUAL(expectedOutputList,b);
}



void deleteOverlappedTest_03(){
	cv::vector<cv::vector<cv::Point> > inputList;
	cv::vector<cv::vector<cv::Point> > expectedOutputList;

	cv::vector<cv::Point> q1;
	q1.push_back(cv::Point(0,0));
	q1.push_back(cv::Point(100,50));
	q1.push_back(cv::Point(200,200));
	q1.push_back(cv::Point(25,300));

	cv::vector<cv::Point> q3;
	q3.push_back(cv::Point(400,400));
	q3.push_back(cv::Point(601,401));
	q3.push_back(cv::Point(800,1000));
	q3.push_back(cv::Point(798,20));

	inputList.push_back(q1);
	inputList.push_back(q3);

	expectedOutputList.push_back(q1);
	expectedOutputList.push_back(q3);

	cv::vector<cv::vector<cv::Point> > b = deleteOverlapped(inputList);
	ASSERT_EQUAL(expectedOutputList,b);
}


void deleteFalseTrianglesTest_01(){
	cv::vector<cv::vector<cv::Point> > inputList;
	cv::vector<cv::vector<cv::Point> > expectedOutputList;

	cv::vector<cv::vector<cv::Point> > b = deleteFalseTriangles(inputList);
	ASSERT_EQUAL(expectedOutputList,b);
}


void deleteFalseTrianglesTest_02(){
	cv::vector<cv::vector<cv::Point> > inputList;
	cv::vector<cv::vector<cv::Point> > expectedOutputList;

	cv::vector<cv::Point> q1;
	q1.push_back(cv::Point(0,0));
	q1.push_back(cv::Point(0,900));
	q1.push_back(cv::Point(900,0));


	inputList.push_back(q1);
	expectedOutputList.push_back(q1);

	cv::vector<cv::vector<cv::Point> > b = deleteFalseTriangles(inputList);
	ASSERT_EQUAL(expectedOutputList,b);
}


void deleteFalseTrianglesTest_03(){
	cv::vector<cv::vector<cv::Point> > inputList;
	cv::vector<cv::vector<cv::Point> > expectedOutputList;

	cv::vector<cv::Point> q2;
	q2.push_back(cv::Point(0,0));
	q2.push_back(cv::Point(0,1));
	q2.push_back(cv::Point(200,0));


	inputList.push_back(q2);

	cv::vector<cv::vector<cv::Point> > b = deleteFalseTriangles(inputList);
	ASSERT_EQUAL(expectedOutputList,b);
}


void deleteFalseTrianglesTest_04(){
	cv::vector<cv::vector<cv::Point> > inputList;
	cv::vector<cv::vector<cv::Point> > expectedOutputList;

	cv::vector<cv::Point> q1;
	q1.push_back(cv::Point(0,0));
	q1.push_back(cv::Point(0,900));
	q1.push_back(cv::Point(900,0));

	cv::vector<cv::Point> q2;
	q2.push_back(cv::Point(0,0));
	q2.push_back(cv::Point(0,1000));
	q2.push_back(cv::Point(1000,0));


	inputList.push_back(q1);
	inputList.push_back(q2);

	expectedOutputList.push_back(q1);
	expectedOutputList.push_back(q2);

	cv::vector<cv::vector<cv::Point> > b = deleteFalseTriangles(inputList);
	ASSERT_EQUAL(expectedOutputList,b);
}


void deleteFalseTrianglesTest_05(){
	cv::vector<cv::vector<cv::Point> > inputList;
	cv::vector<cv::vector<cv::Point> > expectedOutputList;

	cv::vector<cv::Point> q1;
	q1.push_back(cv::Point(0,0));
	q1.push_back(cv::Point(0,900));
	q1.push_back(cv::Point(900,0));

	cv::vector<cv::Point> q2;
	q2.push_back(cv::Point(0,0));
	q2.push_back(cv::Point(0,10));
	q2.push_back(cv::Point(10,0));


	inputList.push_back(q1);
	inputList.push_back(q2);

	expectedOutputList.push_back(q1);

	cv::vector<cv::vector<cv::Point> > b = deleteFalseTriangles(inputList);
	ASSERT_EQUAL(expectedOutputList,b);
}


struct FourPointsSorterTests {

	void error_01(){
		cv::vector<cv::Point> points;
		ASSERT_THROWS(new FourPointsSorter(points),InputException);
	}

	FourPointsSorter *fps;
	//@ATTENTION: the other tests are not there.
	//The testing is made testing 'sort4PointsClockwise' method
};


void sort4PointsClockwiseTest_01(){
	cv::vector<cv::Point> inputPoints;
	cv::vector<cv::Point> expectedSorting;
	cv::vector<cv::Point> actualSorting;

	actualSorting = sort4PointsClockwise(inputPoints);
	ASSERT_EQUAL(expectedSorting,actualSorting);
}


void sort4PointsClockwiseTest_02(){
	cv::vector<cv::Point> inputPoints;
	cv::vector<cv::Point> expectedSorting;
	cv::vector<cv::Point> actualSorting;

	cv::Point p1 = cv::Point(1,2);

	inputPoints.push_back(p1);
	expectedSorting.push_back(p1);

	actualSorting = sort4PointsClockwise(inputPoints);
	ASSERT_EQUAL(expectedSorting,actualSorting);
}


void sort4PointsClockwiseTest_03(){
	cv::vector<cv::Point> inputPoints;
	cv::vector<cv::Point> expectedSorting;
	cv::vector<cv::Point> actualSorting;

	cv::Point p1 = cv::Point(1,2);
	cv::Point p2 = cv::Point(2,2);

	inputPoints.push_back(p1);
	inputPoints.push_back(p2);
	expectedSorting.push_back(p1);
	expectedSorting.push_back(p2);

	actualSorting = sort4PointsClockwise(inputPoints);
	ASSERT_EQUAL(expectedSorting,actualSorting);
}


void sort4PointsClockwiseTest_04(){
	cv::vector<cv::Point> inputPoints;
	cv::vector<cv::Point> expectedSorting;
	cv::vector<cv::Point> actualSorting;

	cv::Point p1 = cv::Point(10,10);
	cv::Point p2 = cv::Point(20,20);
	cv::Point p3 = cv::Point(10,20);

	inputPoints.push_back(p1);
	inputPoints.push_back(p2);
	inputPoints.push_back(p3);
	expectedSorting.push_back(p1);
	expectedSorting.push_back(p3);
	expectedSorting.push_back(p2);

	actualSorting = sort4PointsClockwise(inputPoints);
	ASSERT_EQUAL(expectedSorting,actualSorting);
}


void sort4PointsClockwiseTest_05(){
	cv::vector<cv::Point> inputPoints;
	cv::vector<cv::Point> expectedSorting;
	cv::vector<cv::Point> actualSorting;

	cv::Point p1 = cv::Point(10,10);
	cv::Point p2 = cv::Point(20,20);
	cv::Point p3 = cv::Point(10,20);

	inputPoints.push_back(p3);
	inputPoints.push_back(p2);
	inputPoints.push_back(p1);
	expectedSorting.push_back(p1);
	expectedSorting.push_back(p3);
	expectedSorting.push_back(p2);

	actualSorting = sort4PointsClockwise(inputPoints);
	ASSERT_EQUAL(expectedSorting,actualSorting);
}


void sort4PointsClockwiseTest_06(){
	cv::vector<cv::Point> inputPoints;
	cv::vector<cv::Point> expectedSorting;
	cv::vector<cv::Point> actualSorting;

	cv::Point p1 = cv::Point(10,10);
	cv::Point p2 = cv::Point(20,20);
	cv::Point p3 = cv::Point(10,20);

	inputPoints.push_back(p3);
	inputPoints.push_back(p1);
	inputPoints.push_back(p2);
	expectedSorting.push_back(p1);
	expectedSorting.push_back(p3);
	expectedSorting.push_back(p2);

	actualSorting = sort4PointsClockwise(inputPoints);
	ASSERT_EQUAL(expectedSorting,actualSorting);
}



	/*

	cv::vector <cv::vector<cv::Point> > prova;
	cv::vector<cv::Point> p1;
	p1.push_back(cv::Point(181,45));
	p1.push_back(cv::Point(180,131));
	p1.push_back(cv::Point(267,132));
	p1.push_back(cv::Point(267,46));
	prova.push_back(p1);

	cv::vector<cv::Point> p2;
	p2.push_back(cv::Point(186,46));
	p2.push_back(cv::Point(182,128));
	p2.push_back(cv::Point(263,131));
	p2.push_back(cv::Point(266,50));

	prova.push_back(p2);

	printf("PRIMA\nF %d: ",1);
	for (unsigned int i=0;i<prova.size();i++){
			for (unsigned int j=0;j<prova.at(i).size();j++){
				printf("(%d,%d)  ",prova.at(i).at(j).x,prova.at(i).at(j).y);
			}
			printf("\n\n");
	}

	//ordino in verso antiorario ogni quaterna di vettori
	for ( unsigned int i = 0; i< prova.size(); i++ ) {
		prova.at(i) = sort4PointsClockwise(prova.at(i));
	}

	prova = deleteOverlapped(prova);


	printf("DOPO\nF %d: ",1);
	for (unsigned int i=0;i<prova.size();i++){
			for (unsigned int j=0;j<prova.at(i).size();j++){
				printf("(%d,%d)  ",prova.at(i).at(j).x,prova.at(i).at(j).y);
			}
			printf("\n\n");
	}
	ASSERTM("start writing tests", true);
	*/

void debug(){
	cv::vector<cv::Point> a;
	a.push_back(cv::Point(252,377));
	a.push_back(cv::Point(258,495));
	a.push_back(cv::Point(495,492));
	a.push_back(cv::Point(491,377));

	cv::vector<cv::Point> b;
	b.push_back(cv::Point(256,387));
	b.push_back(cv::Point(260,493));
	b.push_back(cv::Point(493,490));
	b.push_back(cv::Point(488,381));

	bool sim = similar(a,b);
	ASSERT_EQUAL(true,sim);
}




cute::suite make_suite_extractorUtilsTest(){
	cute::suite s;
	s.push_back(CUTE(myDistanceTest_01));
	s.push_back(CUTE(myDistanceTest_02));
	s.push_back(CUTE(myDistanceTest_03));
	s.push_back(CUTE(myDistanceTest_04));
	s.push_back(CUTE(myDistanceTest_05));
	s.push_back(CUTE(myDistanceTest_06));
	s.push_back(CUTE(myDistanceTest_07));


	s.push_back(CUTE(tooCloseTest_01));
	s.push_back(CUTE(tooCloseTest_02));
	s.push_back(CUTE(tooCloseTest_03));

	s.push_back(CUTE(isFalseTest_01));
	s.push_back(CUTE(isFalseTest_02));

	s.push_back(CUTE(isTriangleTest_01));
	s.push_back(CUTE(isTriangleTest_02));

	s.push_back(CUTE(similar_01));
	s.push_back(CUTE(similar_02));
	s.push_back(CUTE(similar_03));
	s.push_back(CUTE(similar_04));

	s.push_back(CUTE(deleteFalseSquaresTest_01));
	s.push_back(CUTE(deleteFalseSquaresTest_02));
	s.push_back(CUTE(deleteFalseSquaresTest_03));
	s.push_back(CUTE(deleteFalseSquaresTest_04));

	s.push_back(CUTE(squareSortTest_01));
	s.push_back(CUTE(squareSortTest_02));
	s.push_back(CUTE(squareSortTest_03));
	s.push_back(CUTE(squareSortTest_04));

	s.push_back(CUTE(deleteOverlappedTest_01));
	s.push_back(CUTE(deleteOverlappedTest_02));
	s.push_back(CUTE(deleteOverlappedTest_03));

	s.push_back(CUTE(deleteFalseTrianglesTest_01));
	s.push_back(CUTE(deleteFalseTrianglesTest_02));
	s.push_back(CUTE(deleteFalseTrianglesTest_03));
	s.push_back(CUTE(deleteFalseTrianglesTest_04));
	s.push_back(CUTE(deleteFalseTrianglesTest_05));

	s+= CUTE_SMEMFUN(FourPointsSorterTests,error_01);

	s.push_back(CUTE(sort4PointsClockwiseTest_01));
	s.push_back(CUTE(sort4PointsClockwiseTest_02));
	s.push_back(CUTE(sort4PointsClockwiseTest_03));
	s.push_back(CUTE(sort4PointsClockwiseTest_04));
	s.push_back(CUTE(sort4PointsClockwiseTest_05));
	s.push_back(CUTE(sort4PointsClockwiseTest_06));

	s.push_back(CUTE(debug));

	return s;
}



