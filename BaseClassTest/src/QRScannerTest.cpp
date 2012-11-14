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
	QRScanner * qrs = new QRScanner("./debian.or.jp.qr.jpg");
	string check = "decoded QR-Code symbol \"http://www.debian.or.jp \n\n\n\nMEBKM:TITLE:DebianJP;URL:http\\://www.debian.or.jp;;";
	string str = qrs->getQRCode();
	str.erase(std::remove_if(str.begin(), str.end(), (int(*)(int))isspace), str.end());

	check.erase(std::remove_if(check.begin(), check.end(), (int(*)(int))isspace), check.end());
//	str.erase(std::remove_if(str.begin(), str.end(), (int(*)(int))'\"'), str.end());
//	ASSERT_EQUAL(",str);//

}

cute::suite make_suite_QRScannerTest(){
	cute::suite s;
	s.push_back(CUTE(QRScannerTest01));
	return s;
}
