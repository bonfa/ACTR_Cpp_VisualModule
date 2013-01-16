/*
 *  proxy.cpp
 *  library
 *
 *  Created by Stefano Bennati on 11/9/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "proxy.h"

void Proxy::demo() {
	//img = inputModule->getImage("./shapes.png");
	//img = inputModule->getImage("./ellipses.jpg");
	//img = inputModule->getImage("./images/01_02_1030797656577.bmp");
	//img = inputModule->getImage("./images/02_08_447099175936.bmp");
	//img = inputModule->getImage("./images/03_32_9007255098753112.bmp");
	//img = inputModule->getImage("./images/04_36_1478332047688192.bmp");
	//img = inputModule->getImage("./images/05_50_1548318539776144.bmp");
	//img = inputModule->getImage("./images/06_54_18023194906722704.bmp");
	//img = inputModule->getImage("./images/07_04_219903404277765.bmp");
	//img = inputModule->getImage("./images/08_06_114392163942656.bmp");
	//img = inputModule->getImage("./images/09_25_1337006283030553.bmp");
	//img = inputModule->getImage("./images/10_26_1548114663047204.bmp");
	//img = inputModule->getImage("./images/11_29_11261199174860888.bmp");
	//img = inputModule->getImage("./images/12_53_145525316052451328.bmp");		//TODO quadrato esterno
	//img = inputModule->getImage("./images/13_59_142118473433600.bmp");		//TODO	quadrato esterno
	//img = inputModule->getImage("./images/14_NA_498222760961.bmp");
	//img = inputModule->getImage("./images/15_NA_10793261728000.bmp");
	//img = inputModule->getImage("./images/16_NA_211142744211593.bmp");
	//img = inputModule->getImage("./images/17_NA_72480910316142593.bmp");		//TODO  quadrato esterno
	//img = inputModule->getImage("./images/18_NA_577445915800635392.bmp");
	//img = inputModule->getImage("./images/19_NA_580260668791324672.bmp");		//TODO	quadrato esterno
	//img = inputModule->getImage("./images/20_NA_583224952673546240.bmp");
	//img = inputModule->getImage("./images/21_NA_584350852048749056.bmp");
	//img = inputModule->getImage("./images/22_NA_865966563026534912.bmp");
	//img = inputModule->getImage("./images/23_NA_867083665762158848.bmp");
	string imgPath = "./images/24_M01_216770917518016516.bmp";

	FeatureGetter *fg = new FeatureGetter(imgPath);

	fg->updateImage();

	fg->showImage();

	fg->setFeatureList();
	//fg->startVideoCapture();
	//fg->showVideo();

	vector<string> chunkList = fg->getObjectChunkList();

	//printChunkList
	for (unsigned int i=0; i<chunkList.size();i++){
			cout << chunkList.at(i) << endl;
		}


	fg->terminate();
	delete fg;
}

void Proxy::demoEnrico() {
	FeatureGetter *fg = new FeatureGetter(1);

	//fg->startVideoCapture();
	//fg->showVideo();

	fg->terminate();

	delete fg;
}

int Proxy::test() {

	return 10;
}

double Proxy::area(){
	Triangle * tri = new Triangle(0,0,2,0,0,2);
	return tri->getArea();
}




