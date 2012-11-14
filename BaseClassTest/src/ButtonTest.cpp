#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "ButtonTest.h"
#include <iostream>
#include <string>


void ButtonTest_Constructor_01(){
	int ax = 0;
	int ay = 0;
	int width = 2;
	int height = 2;
	string buttonText = "questo è un bottone";
	Button *b = new Button(ax,ay,width,height,buttonText);
	ASSERT(b!=NULL);
}


void ButtonTest_ParameterCheck_01(){
	int ax = 0;
	int ay = 0;
	int width = 2;
	int height = 2;
	string buttonText = "questo è un bottone";

	string expectedText = "cianc, bottone\n";
	Button *q = new Button(ax,ay,width,height,buttonText);

	string realChunkString = q->getChunk();
	ASSERT_EQUAL(expectedText,realChunkString);

	string realText = q->getText();
	ASSERT_EQUAL(buttonText,realText);
}


void ButtonTest_ParameterError_01(){
	int ax = 0;
	int ay = 0;
	int width = -2;
	int height = 2;
	string testo = "questo è un bottone";


	string actualChunkString = "cianc, bottone\n";
	ASSERT_THROWS(new Button(ax,ay,width,height,testo),InputException);
}


void ButtonTest_ParameterError_02(){
	int ax = -1;
	int ay = 0;
	int width = 1;
	int height = 1;
	string testo = "questo è un bottone";


	string actualChunkString = "cianc, bottone\n";
	ASSERT_THROWS(new Button(ax,ay,width,height,testo),InputException);
}

void ButtonTest_ParameterError_03(){
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
	s.push_back(CUTE(ButtonTest_Constructor_01));
	s.push_back(CUTE(ButtonTest_ParameterCheck_01));
	s.push_back(CUTE(ButtonTest_ParameterError_01));
	s.push_back(CUTE(ButtonTest_ParameterError_02));
	s.push_back(CUTE(ButtonTest_ParameterError_03));
	return s;
}



