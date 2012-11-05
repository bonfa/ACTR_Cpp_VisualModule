#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "ButtonTest.h"

void ButtonTest01(){
	int ax = 0;
	int ay = 0;
	int width = 2;
	int height = 2;
	string testo = "questo è un bottone";


	string actualChunkString = "cianc, bottone\n";
	Button *q = new Button(ax,ay,width,height,testo);

	string realChunkString = q->getChunk();
	ASSERT_EQUAL(actualChunkString,realChunkString);

}


cute::suite make_suite_ButtonTest(){
	cute::suite s;
	s.push_back(CUTE(ButtonTest01));
	return s;
}



