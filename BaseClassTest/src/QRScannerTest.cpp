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

void QRScannerTest02(){
	QRScanner * qrs = new QRScanner("./qrcamtest.jpg");


	string check = "Test";

	ASSERT_EQUAL(qrs->getQRCode(),"QR-CodeTest");

}

void QRScannerTest03(){
	QRScanner * qrs = new QRScanner("./qrcamtest2.jpg");




	ASSERT_EQUAL(false,qrs->QRDetected());

}

void QRScannerTest04(){
	QRScanner * qrs = new QRScanner("./qrcamtest3.jpg");


	string check = "Test";

	ASSERT_EQUAL("QR-CodeTest",qrs->getQRCode());

}

void QRScannerTest05(){
	QRScanner * qrs = new QRScanner("./qrcamtest4.jpg");


	string check = "Test";

	ASSERT_EQUAL("QR-CodeTest",qrs->getQRCode());

}


void QRScannerTest06(){
	QRScanner * qrs = new QRScanner("./qrcamtest5.jpg");


	string check = "Test";

	ASSERT_EQUAL("QR-CodeTest",qrs->getQRCode());

}

void QRScannerTest07(){
	QRScanner * qrs = new QRScanner("./qrcamtest6.jpg");


	string check = "Test";

	ASSERT_EQUAL("QR-CodeTest",qrs->getQRCode());

}

void QRScannerTest08(){
	QRScanner * qrs = new QRScanner("./qrcamtest7.jpg");


	string check = "Test";

	ASSERT_EQUAL(false,qrs->QRDetected());

}

void QRScannerTest09(){
	QRScanner * qrs = new QRScanner("./qrcamtest8.jpg"); //foto scattata dallo schermo di Francesco verso il muro dietro Enrico


	string check = "Test";

	ASSERT_EQUAL("QR-CodeTest",qrs->getQRCode());

}

void QRScannerTest10(){
	QRScanner * qrs = new QRScanner("./qrcamtest9.jpg");


	string check = "Test";

	ASSERT_EQUAL(false,qrs->QRDetected());

}

cute::suite make_suite_QRScannerTest(){
	cute::suite s;
	s.push_back(CUTE(QRScannerTest01));
	s.push_back(CUTE(QRScannerTest02));
	s.push_back(CUTE(QRScannerTest03));
	s.push_back(CUTE(QRScannerTest04));
	s.push_back(CUTE(QRScannerTest05));
	s.push_back(CUTE(QRScannerTest06));
	s.push_back(CUTE(QRScannerTest07));
	s.push_back(CUTE(QRScannerTest08));
	s.push_back(CUTE(QRScannerTest09));
	s.push_back(CUTE(QRScannerTest10));
	return s;
}
