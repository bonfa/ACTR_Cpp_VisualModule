/*
 * Input.h
 *
 *      Author: enrico
 *
 */

#include "author.h"

//#ifdef ENRICO

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

#define  OBJ1_PATT_NAME    "Data/patt.hiro"
#define  OBJ2_PATT_NAME    "Data/patt.kanji"
#define  OBJ1_SIZE         80.0
#define  OBJ2_SIZE         80.0

#define  OBJ1_MODEL_ID      1
#define  OBJ2_MODEL_ID      2

int stub();
void startDetection();

#endif /* MDETECT_H_ */



// #endif /* ENRICO */
