#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "ButtonTest.h"
#include <iostream>
#include <string>


struct ConstructorError{
	void ButtonTest_ParameterError_01(){
		int ax = -1;
		int ay = 0;
		int width = 2;
		int height = 2;
		string testo = "questo è un bottone";

		ASSERT_THROWS(new Button(ax,ay,width,height,testo),InputException);
	}


	void ButtonTest_ParameterError_02(){
		int ax = 0;
		int ay = -1;
		int width = 1;
		int height = 1;
		string testo = "questo è un bottone";

		ASSERT_THROWS(new Button(ax,ay,width,height,testo),InputException);
	}


	void ButtonTest_ParameterError_03(){
		int ax = 0;
		int ay = 0;
		int width = -1;
		int height = 1;
		string testo = "questo è un bottone";

		ASSERT_THROWS(new Button(ax,ay,width,height,testo),InputException);
	}


	void ButtonTest_ParameterError_04(){
		int ax = 0;
		int ay = 0;
		int width = 1;
		int height = -1;
		string testo = "questo è un bottone";

		ASSERT_THROWS(new Button(ax,ay,width,height,testo),InputException);
	}


	void ButtonTest_ParameterError_05(){
		int ax = 1;
		int ay = 10;
		int width = 1;
		int height = 1;
		string testo = "";

		ASSERT_THROWS(new Button(ax,ay,width,height,testo),InputException);
	}
};


struct ButtonTest_01{

	ButtonTest_01(): b(0,0,2,2,"questo è un bottone"){
		expectedText = "questo è un bottone";
		expectedChunk = "cianc, bottone\n";
	}


	void constructorCheck(){
		ASSERT(&b!=NULL);
	}


	void textCheck(){
		ASSERT_EQUAL(expectedText,b.getText());

	}

	void chunkCheck(){
		ASSERT_EQUAL(expectedChunk,b.getChunk());
	}

	string expectedText;
	string expectedChunk;
	Button b;
};




cute::suite make_suite_ButtonTest(){
	cute::suite s;
	s+= CUTE_SMEMFUN(ButtonTest_01,constructorCheck);
	s+= CUTE_SMEMFUN(ButtonTest_01,textCheck);
	s+= CUTE_SMEMFUN(ButtonTest_01,chunkCheck);
	s+= CUTE_SMEMFUN(ConstructorError,ButtonTest_ParameterError_01);
	s+= CUTE_SMEMFUN(ConstructorError,ButtonTest_ParameterError_02);
	s+= CUTE_SMEMFUN(ConstructorError,ButtonTest_ParameterError_03);
	s+= CUTE_SMEMFUN(ConstructorError,ButtonTest_ParameterError_04);
	s+= CUTE_SMEMFUN(ConstructorError,ButtonTest_ParameterError_05);
	return s;
}



