#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "RectTest.h"

void RectTest01() {
	int x = 0;
	int y = 0;
	int height = 2;
	int width = 1;

	Rect *r = new Rect(x,y,height,width);
	ASSERT_EQUAL(x,r->x);
	ASSERT_EQUAL(y,r->y);
	ASSERT_EQUAL(height,r->height);
	ASSERT_EQUAL(width,r->width);
}

cute::suite make_suite_RectTest(){
	cute::suite s;
	s.push_back(CUTE(RectTest01));
	return s;
}



