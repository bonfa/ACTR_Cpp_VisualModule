#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "BlobTest.h"

void BlobTest01(){
	;
}

cute::suite make_suite_BlobTest(){
	cute::suite s;
	s.push_back(CUTE(BlobTest01));
	return s;
}



