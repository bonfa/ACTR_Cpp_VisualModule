/*
 * Input.h
 *
 *      Author: enrico
 *
 */

#include "author.h"

#ifdef ENRICO

#ifndef MDETECT_H_
#define MDETECT_H_

#ifdef _WIN32
#  include <windows.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#ifndef __APPLE__
#  include <GL/glut.h>
#else
#  include <GLUT/glut.h>
#endif
#include <AR/gsub.h>
#include <AR/video.h>
#include <AR/param.h>
#include <AR/ar.h>

#include <boost/thread/mutex.hpp>
#include "Quadrilateral.h"

#define  OBJ1_PATT_NAME    "Data/patt.hiro"
#define  OBJ2_PATT_NAME    "Data/patt.kanji"
#define  OBJ1_SIZE         80.0
#define  OBJ2_SIZE         80.0

#define  OBJ1_MODEL_ID      1
#define  OBJ2_MODEL_ID      2

//public static boost::mutex mutex_;

	int stub();
	
	static boost::mutex io_mutex;
	void startDetection();//boost::mutex& mutex);
	static std::vector<Quadrilateral *> markersList;
	std::vector<Quadrilateral *> getMarkers();
#endif /* MDETECT_H_ */

#else
#include "Quadrilateral.h"
	static std::vector<Quadrilateral *> getMarkers(){
		return NULL;
	};

#endif /* ENRICO */
