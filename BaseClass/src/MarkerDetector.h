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

#define IMG_PATH "img.jpg"

#define CRP_IM1 "crop1.jpg"
#define CRP_IM2 "crop2.jpg"

	#ifdef _WIN32
	#  include <windows.h>
	#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef __APPLE__
#  include <GL/glut.h>
#  ifdef GL_VERSION_1_2
#    include <GL/glext.h>
#  endif
#else
#  include <GLUT/glut.h>
#  include <OpenGL/glext.h>
#endif
#include <AR/gsub.h>
#include <AR/config.h>
#include <AR/video.h>
#include <AR/param.h>
#include <AR/ar.h>
#include <AR/gsub_lite.h>


#include <cv.hpp>
#include <cxcore.hpp>
#include <cv.h>
#include <highgui.h>
#include <legacy/legacy.hpp>
#include <math.h>
#include <boost/thread/mutex.hpp>
#include "Marker.h"

#include <boost/filesystem.hpp>
//using namespace boost::filesystem;

#define  OBJ1_PATT_NAME    "Data/patt.hiro"
#define  OBJ2_PATT_NAME    "Data/patt.kanji"
#define  OBJ1_SIZE         80.0
#define  OBJ2_SIZE         80.0

#define  OBJ1_MODEL_ID      1
#define  OBJ2_MODEL_ID      2

static ARGL_CONTEXT_SETTINGS_REF gArglSettings = NULL;


//public static boost::mutex mutex_;

	int stub();

	static boost::mutex io_mutex;
	void startDetection();//boost::mutex& mutex);
	static std::vector<Quadrilateral *> markersList;
	static std::vector<Quadrilateral *> slowMarkerList;
	std::vector<Quadrilateral *> getMarkers();
	int initMarkersData();
	cv::Mat * getFrame();

#endif /* MDETECT_H_ */

#endif /* ENRICO */
