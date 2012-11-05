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

	string realText = q->getText();
	ASSERT_EQUAL(testo,realText);
}


void ButtonTest02(){
	int ax = 0;
	int ay = 0;
	int width = -2;
	int height = 2;
	string testo = "questo è un bottone";


	string actualChunkString = "cianc, bottone\n";
	ASSERT_THROWS(new Button(ax,ay,width,height,testo),InputException);
}


void ButtonTest03(){
	int ax = -1;
	int ay = 0;
	int width = 1;
	int height = 1;
	string testo = "questo è un bottone";


	string actualChunkString = "cianc, bottone\n";
	ASSERT_THROWS(new Button(ax,ay,width,height,testo),InputException);
}

void ButtonTest04(){
	int ax = 1;
	int ay = 10;
	int width = 1;
	int height = 1;
	string testo = "";


	string actualChunkString = "cianc, bottone\n";
	ASSERT_THROWS(new Button(ax,ay,width,height,testo),InputException);
}



cute::suite make_suite_ButtonTest(){
	cute::suite s;
	s.push_back(CUTE(ButtonTest01));
	s.push_back(CUTE(ButtonTest02));
	s.push_back(CUTE(ButtonTest03));
	s.push_back(CUTE(ButtonTest04));
	return s;
}



