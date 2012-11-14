/*
 * QRScannerTest.cpp
 *
 *  Created on: 13/nov/2012
 *      Author: enrico
 */

#include "QRScannerTest.h"
#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

void QRScannerTest01(){
	QRScanner * qrs = new QRScanner("./qrtest.png");


	string check = "Test";

	ASSERT_EQUAL(qrs->getQRCode(),"QR-CodeTest");

}

cute::suite make_suite_QRScannerTest(){
	cute::suite s;
	s.push_back(CUTE(QRScannerTest01));
	return s;
}
