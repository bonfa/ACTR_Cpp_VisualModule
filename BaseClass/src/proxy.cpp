/*
 *  proxy.cpp
 *  library
 *
 *  Created by Stefano Bennati on 11/9/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "proxy.h"

Proxy::Proxy(string imgPath){
	this->imgPath = imgPath;
}

#ifdef ENRICO
Proxy::Proxy(){
	this->imgPath = "";
	fg = new FeatureGetter(1);
}
#endif
/*
void Proxy::demo() {
	FeatureGetter *fg = new FeatureGetter(imgPath);

	fg->updateImage();

	fg->showImage();

	fg->setFeatureList();
	//fg->startVideoCapture();
	//fg->showVideo();

	std::vector<Object *> objectList = fg->getObjectList();

	std::vector<Object *> cleanedObjectList = this->filterObjectList(objectList);

	std::vector<string> chunkList = this->getChunkList(cleanedObjectList);

	//printChunkList
	//TODO communication with server
	for (unsigned int i=0; i<chunkList.size();i++){
		cout << chunkList.at(i) << endl;
	}


	fg->terminate();
	delete fg;
}
*/

#ifdef ENRICO
vector<string>  Proxy::getMarkerList() {

	fg->setFeatureList();
	//fg->startVideoCapture();
	//fg->showVideo();
	objectList = fg->getObjectList();

	vector<string> chunkList;
	for (unsigned int i=0; i<objectList.size();i++)
		chunkList.push_back(objectList.at(i)->getChunk());
	return chunkList;
}
#endif

int Proxy::test() {

	return 10;
}

double Proxy::area(){
	Triangle * tri = new Triangle(0,0,2,0,0,2,"red");
	return tri->getArea();
}

vector<string> Proxy::getChunkList(){
	// process the image and extract the features
	this->processImage();

	//create and return the chunk list
	vector<string> chunkList;
	for (unsigned int i=0; i<objectList.size();i++)
		chunkList.push_back(objectList.at(i)->getChunk());
	return chunkList;
}

std::vector<Object *> Proxy::filterObjectList(std::vector<Object *> objectList){
	for (unsigned int i=0; i<objectList.size();i++){
		if (objectList.at(i)->getBbox().x < BBOX_THRESH_X || objectList.at(i)->getBbox().y < BBOX_THRESH_Y)
			objectList.erase(objectList.begin()+i);
	}
	return objectList;
}

void Proxy::processImage(){
	FeatureGetter *fg = new FeatureGetter(imgPath);
	fg->updateImage();
	#ifndef NO_IMG_SHOW
	fg->showImage();
	#endif
	fg->setFeatureList();
	std::vector<Object *> temporaryObjectList = fg->getObjectList();
	std::vector<Object *> cleanedObjectList = this->filterObjectList(temporaryObjectList);
	//TODO shift values of 100 px
	this->objectList = cleanedObjectList;
	fg->terminate();
	delete fg;
}

