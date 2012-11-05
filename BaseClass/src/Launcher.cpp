/*
 * Launcher.cpp
 *
 *  Created on: 02/nov/2012
 *      Author: enrico
 */

#include "Circle.h"
#include "Triangle.h"
#include "Quadrilateral.h"
#include "Button.h"
#include "Object.h"
#include "Launcher.h"
#include "BaseClass.h"

#include <opencv/cv.h>
#include <cv.h>
#include <highgui.h>
#include <opencv/cxcore.h>
#include <iostream>

int launch(){
	Button * b = new Button(10,2,20,20,"ciao");
	Circle * c = new Circle(8, 10, 15);
	Quadrilateral * q = new Quadrilateral(1,2,3,4,5,6,7,8);
	Triangle * t = new Triangle(0,1,2,3,4,5);

	std::cout << "Launcher\n";

	std::cout << b->getChunk();
	std::cout << c->getChunk();
	std::cout << q->getChunk();

	std::cout << t->getChunk();

	Object * o = c;

	std::cout << o->getChunk();

	BaseClass *ba = new BaseClass();

	imshow("finestra",ba->getImage("./lena.jpg"));
	waitKey(0);

	VideoCapture cap = ba->getStream();
	ba->showVideo(cap);


	return 0;

}

