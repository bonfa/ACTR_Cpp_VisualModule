/*
 *  proxy.h
 *  library
 *
 *  Created by Stefano Bennati on 11/9/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _PROXY_H
#define _PROXY_H
#include "FeatureGetter.h"
#include "Triangle.h"
#include "author.h"

class Proxy {
public:
	Proxy(string imgPath);
#ifdef ENRICO
	Proxy();
#endif
	//void demo();
	int test();
	double area();
	/** Extract the chunk list from the input object list */
	vector<string> getChunkList();
#ifdef ENRICO
	/** Extract the marker list from the input object list */
	vector<string> getMarkerList();
#endif
private:
	/** the path of the image to process*/
	string imgPath;
	/** the list of the object detected in the image*/
	std::vector<Object *> objectList;
	/** Process the image and extract the features*/
	void processImage();
	/** Adapt the parameters to the specific esperiment
	 * This makes the program not general purpose.
	 * TODO: move this somewhere else*/
	std::vector<Object *> filterObjectList(std::vector<Object *> objectList);
	//std::vector<Object *> shiftObjectList(std::vector<Object *> objectList);
	/** Featuregetter needed to extract markers with ArToolkit */
	FeatureGetter *fg;
};

#endif
