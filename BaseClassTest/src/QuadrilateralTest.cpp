#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "QuadrilateralTest.h"

//Prepare the chunk for the quadrilateral
string createExpectedChunk(int x1,int y1,int x2,int y2,string color){
	string chunk = "{";
			chunk.append("\"object\"");
			chunk.append(":");
			chunk.append("{");
			chunk.append("\"type\": \"Quadrilateral\",");
			chunk.append("\"bbox\": {");
				chunk.append("\"x1\":");
				chunk.append("\"");
				chunk.append(intToString(x1));
				chunk.append("\",");

				chunk.append("\"y1\":");
				chunk.append("\"");
				chunk.append(intToString(y1));
				chunk.append("\",");

				chunk.append("\"x2\":");
				chunk.append("\"");
				chunk.append(intToString(x2));
				chunk.append("\",");

				chunk.append("\"y2\":");
				chunk.append("\"");
				chunk.append(intToString(y2));
				chunk.append("\"");
			chunk.append("}");
			chunk.append(",");
			chunk.append("\"color\": ");
			chunk.append("\"");
			chunk.append(color);
			chunk.append("\"");
			chunk.append("}");
		chunk.append("}");

		return 	chunk;
}


struct ConstructorError{

	void negativeValues_01(){
		int ax = -1;
		int ay = 0;
		int bx = 2;
		int by = 0;
		int cx = 2;
		int cy = 3;
		int dx = 0;
		int dy = 3;

		ASSERT_THROWS(new Quadrilateral(ax,ay,bx,by,cx,cy,dx,dy),InputException);
	}


	void negativeValues_02(){
		int ax = 0;
		int ay = -1;
		int bx = 2;
		int by = 0;
		int cx = 2;
		int cy = 3;
		int dx = 0;
		int dy = 3;

		ASSERT_THROWS(new Quadrilateral(ax,ay,bx,by,cx,cy,dx,dy),InputException);
	}


	void negativeValues_03(){
		int ax = 0;
		int ay = 0;
		int bx = -2;
		int by = 0;
		int cx = 2;
		int cy = 3;
		int dx = 0;
		int dy = 3;

		ASSERT_THROWS(new Quadrilateral(ax,ay,bx,by,cx,cy,dx,dy),InputException);
	}


	void negativeValues_04(){
		int ax = 0;
		int ay = 0;
		int bx = 2;
		int by = -1;
		int cx = 2;
		int cy = 3;
		int dx = 0;
		int dy = 3;

		ASSERT_THROWS(new Quadrilateral(ax,ay,bx,by,cx,cy,dx,dy),InputException);
	}


	void negativeValues_05(){
		int ax = 0;
		int ay = 0;
		int bx = 2;
		int by = 0;
		int cx = -2;
		int cy = 3;
		int dx = 0;
		int dy = 3;

		ASSERT_THROWS(new Quadrilateral(ax,ay,bx,by,cx,cy,dx,dy),InputException);
	}


	void negativeValues_06(){
		int ax = 0;
		int ay = 0;
		int bx = 2;
		int by = 0;
		int cx = 2;
		int cy = -3;
		int dx = 0;
		int dy = 3;

		ASSERT_THROWS(new Quadrilateral(ax,ay,bx,by,cx,cy,dx,dy),InputException);
	}


	void negativeValues_07(){
		int ax = 0;
		int ay = 0;
		int bx = 2;
		int by = 0;
		int cx = 2;
		int cy = 3;
		int dx = -1;
		int dy = 3;

		ASSERT_THROWS(new Quadrilateral(ax,ay,bx,by,cx,cy,dx,dy),InputException);
	}


	void negativeValues_08(){
		int ax = 0;
		int ay = 0;
		int bx = 2;
		int by = 0;
		int cx = 2;
		int cy = 3;
		int dx = 0;
		int dy = -3;

		ASSERT_THROWS(new Quadrilateral(ax,ay,bx,by,cx,cy,dx,dy),InputException);
	}


	void threeCoincidentPoints_01(){
		int ax = 0;
		int ay = 0;
		int bx = 0;
		int by = 0;
		int cx = 0;
		int cy = 0;
		int dx = 1;
		int dy = 12;

		ASSERT_THROWS(new Quadrilateral(ax,ay,bx,by,cx,cy,dx,dy),InputException);
	}


	void threeCoincidentPoints_02(){
		int ax = 0;
		int ay = 0;
		int bx = 0;
		int by = 0;
		int cx = 1;
		int cy = 1;
		int dx = 0;
		int dy = 0;

		ASSERT_THROWS(new Quadrilateral(ax,ay,bx,by,cx,cy,dx,dy),InputException);
	}


	void threeCoincidentPoints_03(){
		int ax = 0;
		int ay = 0;
		int bx = 1;
		int by = 1;
		int cx = 0;
		int cy = 0;
		int dx = 0;
		int dy = 0;

		ASSERT_THROWS(new Quadrilateral(ax,ay,bx,by,cx,cy,dx,dy),InputException);
	}


	void threeCoincidentPoints_04(){
		int ax = 1;
		int ay = 1;
		int bx = 0;
		int by = 0;
		int cx = 0;
		int cy = 0;
		int dx = 0;
		int dy = 0;

		ASSERT_THROWS(new Quadrilateral(ax,ay,bx,by,cx,cy,dx,dy),InputException);
	}


	void twoCoincidentPoints_01(){
		int ax = 1;
		int ay = 1;
		int bx = 1;
		int by = 1;
		int cx = 0;
		int cy = 0;
		int dx = 4;
		int dy = 5;

		ASSERT_THROWS(new Quadrilateral(ax,ay,bx,by,cx,cy,dx,dy),InputException);
	}

	void twoCoincidentPoints_02(){
		int ax = 1;
		int ay = 1;
		int bx = 0;
		int by = 0;
		int cx = 1;
		int cy = 1;
		int dx = 4;
		int dy = 5;

		ASSERT_THROWS(new Quadrilateral(ax,ay,bx,by,cx,cy,dx,dy),InputException);
	}


	void twoCoincidentPoints_03(){
		int ax = 1;
		int ay = 1;
		int bx = 0;
		int by = 0;
		int cx = 4;
		int cy = 5;
		int dx = 1;
		int dy = 1;

		ASSERT_THROWS(new Quadrilateral(ax,ay,bx,by,cx,cy,dx,dy),InputException);
	}


	void twoCoincidentPoints_04(){
		int ax = 0;
		int ay = 0;
		int bx = 1;
		int by = 1;
		int cx = 1;
		int cy = 1;
		int dx = 4;
		int dy = 5;

		ASSERT_THROWS(new Quadrilateral(ax,ay,bx,by,cx,cy,dx,dy),InputException);
	}


	void twoCoincidentPoints_05(){
		int ax = 0;
		int ay = 0;
		int bx = 1;
		int by = 1;
		int cx = 4;
		int cy = 5;
		int dx = 1;
		int dy = 1;

		ASSERT_THROWS(new Quadrilateral(ax,ay,bx,by,cx,cy,dx,dy),InputException);
	}


	void twoCoincidentPoints_06(){
		int ax = 0;
		int ay = 0;
		int bx = 1;
		int by = 1;
		int cx = 4;
		int cy = 5;
		int dx = 4;
		int dy = 5;

		ASSERT_THROWS(new Quadrilateral(ax,ay,bx,by,cx,cy,dx,dy),InputException);
	}


	void inLinePoints_01(){
		int ax = 0;
		int ay = 0;
		int bx = 1;
		int by = 1;
		int cx = 2;
		int cy = 2;
		int dx = 4;
		int dy = 5;

		ASSERT_THROWS(new Quadrilateral(ax,ay,bx,by,cx,cy,dx,dy),InputException);
	}


	void inLinePoints_02(){
		int ax = 0;
		int ay = 0;
		int bx = 1;
		int by = 1;
		int cx = 4;
		int cy = 5;
		int dx = 2;
		int dy = 2;

		ASSERT_THROWS(new Quadrilateral(ax,ay,bx,by,cx,cy,dx,dy),InputException);
	}


	void inLinePoints_03(){
		int ax = 0;
		int ay = 0;
		int bx = 4;
		int by = 5;
		int cx = 1;
		int cy = 1;
		int dx = 2;
		int dy = 2;

		ASSERT_THROWS(new Quadrilateral(ax,ay,bx,by,cx,cy,dx,dy),InputException);
	}


	void inLinePoints_04(){
		int ax = 4;
		int ay = 5;
		int bx = 1;
		int by = 1;
		int cx = 3;
		int cy = 3;
		int dx = 2;
		int dy = 2;

		ASSERT_THROWS(new Quadrilateral(ax,ay,bx,by,cx,cy,dx,dy),InputException);
	}
};


struct QuadrilateralTest_01{

	QuadrilateralTest_01(): q(0,0,2,0,2,2,0,2){
		expectedArea = 4;
		expectedA = Point(0,0);
		expectedB = Point(2,0);
		expectedC = Point(2,2);
		expectedD = Point(0,2);
		expectedRotation = 0;
		expectedBBox = Rect(0,0,2,2);
		expectedCenter = Point(1,1);
		expectedEdgeLines.push_back(Segment(expectedA,expectedB));
		expectedEdgeLines.push_back(Segment(expectedB,expectedC));
		expectedEdgeLines.push_back(Segment(expectedC,expectedD));
		expectedEdgeLines.push_back(Segment(expectedD,expectedA));
		expectedChunkString = createExpectedChunk(expectedA.x,expectedA.y,expectedC.x,expectedC.y,"");
	}

	void Constructor_01(){
		ASSERT_EQUAL(false, &q==NULL);
	}

	void getA(){
		ASSERT_EQUAL(expectedA,q.getA());
	}

	void getB(){
		ASSERT_EQUAL(expectedB,q.getB());
	}

	void getC(){
		ASSERT_EQUAL(expectedC,q.getC());
	}

	void getD(){
		ASSERT_EQUAL(expectedD,q.getD());
	}

	void getChunk(){
		ASSERT_EQUAL(expectedChunkString,q.getChunk());
	}

	void checkRotation(){
		ASSERT_EQUAL(expectedRotation,q.getRotation());
	}

	void checkArea(){
		ASSERT_EQUAL(expectedArea,q.getArea());
	}

	void checkBoundingBox(){
		ASSERT_EQUAL(expectedBBox,q.getBbox());
	}

	void checkCenter(){
		ASSERT_EQUAL(expectedCenter,q.getCenter());
	}

	void checkEdgelines(){
		std::vector<Segment> lines = q.getEdgesLine();
		ASSERT_EQUAL(expectedEdgeLines,lines);
	}

	Quadrilateral q;
	Point expectedA;
	Point expectedB;
	Point expectedC;
	Point expectedD;
	string expectedChunkString;
	double expectedArea;
	double expectedRotation;
	Rect expectedBBox;
	Point expectedCenter;
	std::vector<Segment> expectedEdgeLines;
};



struct QuadrilateralTest_02{

	QuadrilateralTest_02(): q(0,0,2,0,2,3,0,3){
		expectedArea = 6.0;
		expectedA = Point(0,0);
		expectedB = Point(2,0);
		expectedC = Point(2,3);
		expectedD = Point(0,3);
		expectedRotation = 0;
		expectedBBox = Rect(0,0,3,2);
		expectedCenter = Point(1,1.5);
		expectedEdgeLines.push_back(Segment(expectedA,expectedB));
		expectedEdgeLines.push_back(Segment(expectedB,expectedC));
		expectedEdgeLines.push_back(Segment(expectedC,expectedD));
		expectedEdgeLines.push_back(Segment(expectedD,expectedA));
		expectedChunkString = createExpectedChunk(expectedA.x,expectedA.y,expectedC.x,expectedC.y,"");
	}

	void Constructor_01(){
		ASSERT_EQUAL(false, &q==NULL);
	}

	void getA(){
		ASSERT_EQUAL(expectedA,q.getA());
	}

	void getB(){
		ASSERT_EQUAL(expectedB,q.getB());
	}

	void getC(){
		ASSERT_EQUAL(expectedC,q.getC());
	}

	void getD(){
		ASSERT_EQUAL(expectedD,q.getD());
	}

	void getChunk(){
		ASSERT_EQUAL(expectedChunkString,q.getChunk());
	}

	void checkRotation(){
		ASSERT_EQUAL(expectedRotation,q.getRotation());
	}

	void checkArea(){
		ASSERT_EQUAL(expectedArea,q.getArea());
	}

	void checkBoundingBox(){
		ASSERT_EQUAL(expectedBBox,q.getBbox());
	}

	void checkCenter(){
		ASSERT_EQUAL(expectedCenter,q.getCenter());
	}

	void checkEdgelines(){
		std::vector<Segment> lines = q.getEdgesLine();
		ASSERT_EQUAL(expectedEdgeLines,lines);
	}

	Quadrilateral q;
	Point expectedA;
	Point expectedB;
	Point expectedC;
	Point expectedD;
	string expectedChunkString;
	double expectedArea;
	double expectedRotation;
	Rect expectedBBox;
	Point expectedCenter;
	std::vector<Segment> expectedEdgeLines;
};



struct QuadrilateralTest_03{

	QuadrilateralTest_03(): q(0,0,1,1,1,2,0,1){
		expectedArea = 1.0;
		expectedA = Point(0,0);
		expectedB = Point(1,1);
		expectedC = Point(1,2);
		expectedD = Point(0,1);
		expectedRotation = M_PI/4;
		expectedBBox = Rect(0,0,2,1);
		expectedCenter = Point(0.5,1);
		expectedEdgeLines.push_back(Segment(expectedA,expectedB));
		expectedEdgeLines.push_back(Segment(expectedB,expectedC));
		expectedEdgeLines.push_back(Segment(expectedC,expectedD));
		expectedEdgeLines.push_back(Segment(expectedD,expectedA));
		expectedChunkString = createExpectedChunk(expectedA.x,expectedA.y,expectedC.x,expectedC.y,"");
	}

	void Constructor_01(){
		ASSERT_EQUAL(false, &q==NULL);
	}

	void getA(){
		ASSERT_EQUAL(expectedA,q.getA());
	}

	void getB(){
		ASSERT_EQUAL(expectedB,q.getB());
	}

	void getC(){
		ASSERT_EQUAL(expectedC,q.getC());
	}

	void getD(){
		ASSERT_EQUAL(expectedD,q.getD());
	}

	void getChunk(){
		ASSERT_EQUAL(expectedChunkString,q.getChunk());
	}

	void checkRotation(){
		ASSERT_EQUAL(expectedRotation,q.getRotation());
	}

	void checkArea(){
		ASSERT_EQUAL(expectedArea,q.getArea());
	}

	void checkBoundingBox(){
		ASSERT_EQUAL(expectedBBox,q.getBbox());
	}

	void checkCenter(){
		ASSERT_EQUAL(expectedCenter,q.getCenter());
	}

	void checkEdgelines(){
		std::vector<Segment> lines = q.getEdgesLine();
		ASSERT_EQUAL(expectedEdgeLines,lines);
	}

	Quadrilateral q;
	Point expectedA;
	Point expectedB;
	Point expectedC;
	Point expectedD;
	string expectedChunkString;
	double expectedArea;
	double expectedRotation;
	Rect expectedBBox;
	Point expectedCenter;
	std::vector<Segment> expectedEdgeLines;
};


struct QuadrilateralTest_04{

	QuadrilateralTest_04(): q(2,0,2,1,1,2,1,1){
		expectedArea = 1.0;
		expectedA = Point(2,0);
		expectedB = Point(2,1);
		expectedC = Point(1,2);
		expectedD = Point(1,1);
		expectedRotation = M_PI/2;
		expectedBBox = Rect(1,0,2,1);
		expectedCenter = Point(1.5,1);
		expectedEdgeLines.push_back(Segment(expectedA,expectedB));
		expectedEdgeLines.push_back(Segment(expectedB,expectedC));
		expectedEdgeLines.push_back(Segment(expectedC,expectedD));
		expectedEdgeLines.push_back(Segment(expectedD,expectedA));
		expectedChunkString = createExpectedChunk(1,0,2,2,"");
	}

	void Constructor_01(){
		ASSERT_EQUAL(false, &q==NULL);
	}

	void getA(){
		ASSERT_EQUAL(expectedA,q.getA());
	}

	void getB(){
		ASSERT_EQUAL(expectedB,q.getB());
	}

	void getC(){
		ASSERT_EQUAL(expectedC,q.getC());
	}

	void getD(){
		ASSERT_EQUAL(expectedD,q.getD());
	}

	void getChunk(){
		ASSERT_EQUAL(expectedChunkString,q.getChunk());
	}

	void checkRotation(){
		ASSERT_EQUAL(expectedRotation,q.getRotation());
	}

	void checkArea(){
		ASSERT_EQUAL(expectedArea,q.getArea());
	}

	void checkBoundingBox(){
		ASSERT_EQUAL(expectedBBox,q.getBbox());
	}

	void checkCenter(){
		ASSERT_EQUAL(expectedCenter,q.getCenter());
	}

	void checkEdgelines(){
		std::vector<Segment> lines = q.getEdgesLine();
		ASSERT_EQUAL(expectedEdgeLines,lines);
	}

	Quadrilateral q;
	Point expectedA;
	Point expectedB;
	Point expectedC;
	Point expectedD;
	string expectedChunkString;
	double expectedArea;
	double expectedRotation;
	Rect expectedBBox;
	Point expectedCenter;
	std::vector<Segment> expectedEdgeLines;
};



cute::suite make_suite_QuadrilateralTest(){
	cute::suite s;

	s+= CUTE_SMEMFUN(ConstructorError,negativeValues_01);
	s+= CUTE_SMEMFUN(ConstructorError,negativeValues_02);
	s+= CUTE_SMEMFUN(ConstructorError,negativeValues_03);
	s+= CUTE_SMEMFUN(ConstructorError,negativeValues_04);
	s+= CUTE_SMEMFUN(ConstructorError,negativeValues_05);
	s+= CUTE_SMEMFUN(ConstructorError,negativeValues_06);
	s+= CUTE_SMEMFUN(ConstructorError,negativeValues_07);
	s+= CUTE_SMEMFUN(ConstructorError,negativeValues_08);
	s+= CUTE_SMEMFUN(ConstructorError,threeCoincidentPoints_01);
	s+= CUTE_SMEMFUN(ConstructorError,threeCoincidentPoints_02);
	s+= CUTE_SMEMFUN(ConstructorError,threeCoincidentPoints_03);
	s+= CUTE_SMEMFUN(ConstructorError,threeCoincidentPoints_04);
	s+= CUTE_SMEMFUN(ConstructorError,twoCoincidentPoints_01);
	s+= CUTE_SMEMFUN(ConstructorError,twoCoincidentPoints_02);
	s+= CUTE_SMEMFUN(ConstructorError,twoCoincidentPoints_03);
	s+= CUTE_SMEMFUN(ConstructorError,twoCoincidentPoints_04);
	s+= CUTE_SMEMFUN(ConstructorError,twoCoincidentPoints_05);
	s+= CUTE_SMEMFUN(ConstructorError,twoCoincidentPoints_06);
	s+= CUTE_SMEMFUN(ConstructorError,inLinePoints_01);
	s+= CUTE_SMEMFUN(ConstructorError,inLinePoints_02);
	s+= CUTE_SMEMFUN(ConstructorError,inLinePoints_03);
	s+= CUTE_SMEMFUN(ConstructorError,inLinePoints_04);

	s+= CUTE_SMEMFUN(QuadrilateralTest_01,Constructor_01);
	s+= CUTE_SMEMFUN(QuadrilateralTest_01,getA);
	s+= CUTE_SMEMFUN(QuadrilateralTest_01,getB);
	s+= CUTE_SMEMFUN(QuadrilateralTest_01,getC);
	s+= CUTE_SMEMFUN(QuadrilateralTest_01,getD);
	s+= CUTE_SMEMFUN(QuadrilateralTest_01,getChunk);
	s+= CUTE_SMEMFUN(QuadrilateralTest_01,checkRotation);
	s+= CUTE_SMEMFUN(QuadrilateralTest_01,checkArea);
	s+= CUTE_SMEMFUN(QuadrilateralTest_01,checkBoundingBox);
	s+= CUTE_SMEMFUN(QuadrilateralTest_01,checkCenter);
	s+= CUTE_SMEMFUN(QuadrilateralTest_01,checkEdgelines);

	s+= CUTE_SMEMFUN(QuadrilateralTest_02,Constructor_01);
	s+= CUTE_SMEMFUN(QuadrilateralTest_02,getA);
	s+= CUTE_SMEMFUN(QuadrilateralTest_02,getB);
	s+= CUTE_SMEMFUN(QuadrilateralTest_02,getC);
	s+= CUTE_SMEMFUN(QuadrilateralTest_02,getD);
	s+= CUTE_SMEMFUN(QuadrilateralTest_02,getChunk);
	s+= CUTE_SMEMFUN(QuadrilateralTest_02,checkRotation);
	s+= CUTE_SMEMFUN(QuadrilateralTest_02,checkArea);
	s+= CUTE_SMEMFUN(QuadrilateralTest_02,checkBoundingBox);
	s+= CUTE_SMEMFUN(QuadrilateralTest_02,checkCenter);
	s+= CUTE_SMEMFUN(QuadrilateralTest_02,checkEdgelines);

	s+= CUTE_SMEMFUN(QuadrilateralTest_03,Constructor_01);
	s+= CUTE_SMEMFUN(QuadrilateralTest_03,getA);
	s+= CUTE_SMEMFUN(QuadrilateralTest_03,getB);
	s+= CUTE_SMEMFUN(QuadrilateralTest_03,getC);
	s+= CUTE_SMEMFUN(QuadrilateralTest_03,getD);
	s+= CUTE_SMEMFUN(QuadrilateralTest_03,getChunk);
	s+= CUTE_SMEMFUN(QuadrilateralTest_03,checkRotation);
	s+= CUTE_SMEMFUN(QuadrilateralTest_03,checkArea);
	s+= CUTE_SMEMFUN(QuadrilateralTest_03,checkBoundingBox);
	s+= CUTE_SMEMFUN(QuadrilateralTest_03,checkCenter);
	s+= CUTE_SMEMFUN(QuadrilateralTest_03,checkEdgelines);

	s+= CUTE_SMEMFUN(QuadrilateralTest_04,Constructor_01);
	s+= CUTE_SMEMFUN(QuadrilateralTest_04,getA);
	s+= CUTE_SMEMFUN(QuadrilateralTest_04,getB);
	s+= CUTE_SMEMFUN(QuadrilateralTest_04,getC);
	s+= CUTE_SMEMFUN(QuadrilateralTest_04,getD);
	s+= CUTE_SMEMFUN(QuadrilateralTest_04,getChunk);
	s+= CUTE_SMEMFUN(QuadrilateralTest_04,checkRotation);
	s+= CUTE_SMEMFUN(QuadrilateralTest_04,checkArea);
	s+= CUTE_SMEMFUN(QuadrilateralTest_04,checkBoundingBox);
	s+= CUTE_SMEMFUN(QuadrilateralTest_04,checkCenter);
	s+= CUTE_SMEMFUN(QuadrilateralTest_04,checkEdgelines);

	return s;
}



