#include <iostream>
#include <Magick++.h>
#include <zbar.h>


#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv/cxcore.h>

#include "QRScanner.h"

using namespace std;
using namespace zbar;

QRScanner::QRScanner(string path){
	CvMat *cv_matrix = cvLoadImageM(path.c_str(),CV_LOAD_IMAGE_GRAYSCALE); //"./debian.or.jp.qr.jpg"

	int width = cv_matrix->width;
	int height= cv_matrix->height;
	char *raw = (char*)cv_matrix->data.ptr;

	// create a reader
	ImageScanner scanner;

	// configure the reader
	scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);

	image = new Image(width, height, "Y800", raw, width * height);

	// scan the image for barcodes
	numLines = scanner.scan(*image);
};

QRScanner::~QRScanner(){
	image->set_data(NULL, 0);
	delete image;
}


bool QRScanner::QRDetected(){
	return numLines>0;
}

string QRScanner::getQRCode()
{
    stringstream out;

    // extract results
    for(Image::SymbolIterator symbol = image->symbol_begin();
    		symbol != image->symbol_end();
    		++symbol) {
    	out << symbol->get_type_name() << symbol->get_data();
    	// do something useful with results
    	//cout << "decoded " << symbol->get_type_name()
        //     << " symbol \"" << symbol->get_data() << '"' << endl;
    }

    return  out.str();
}



