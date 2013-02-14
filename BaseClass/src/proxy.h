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

//value under which the boundingbox of one object (and the object itself) is considered invalid
#define BBOX_THRESH_X 9
#define BBOX_THRESH_Y 9
//95 for the rush-hour images and 20 for the shapes image

class Proxy {
public:
	Proxy(string imgPath);
	Proxy();
	//void demo();
	int test();
	double area();
	/** Extract the chunk list from the input object list */
	vector<string> getChunkList();
	/** Extract the marker list from the input object list */
	vector<string> getMarkerList();
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
