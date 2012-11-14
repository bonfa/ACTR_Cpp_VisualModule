#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "MyPointTest.h"

void PointTest01() {
	int ax = 5;
	int ay = 4;

	Point *p = new Point(ax,ay);
	ASSERT_EQUAL(ax, p->x);
	ASSERT_EQUAL(ay,p->y);

}

cute::suite make_suite_MyPointTest(){
	cute::suite s;
	s.push_back(CUTE(PointTest01));
	return s;
}



