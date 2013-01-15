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
	FeatureGetter *fg = new FeatureGetter();

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

int Proxy::test() {

	return 10;
}

double Proxy::area(){
	Triangle * tri = new Triangle(0,0,2,0,0,2);
	return tri->getArea();
}




