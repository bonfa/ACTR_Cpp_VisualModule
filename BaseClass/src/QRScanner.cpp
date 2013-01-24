
#include "author.h"

#include "QRScanner.h"

#ifdef ENRICO
using namespace std;
using namespace zbar;
using namespace cv;

QRScanner::QRScanner(cv::Mat * img){
	cv::Mat  greyMat;
	cv::cvtColor(*img, greyMat, CV_BGR2GRAY);

	CvMat tempImg = greyMat;

	init((char*)tempImg.data.ptr,tempImg.width,tempImg.height);
}

void QRScanner::init(char *raw, int width,int height){
	// create a reader
	ImageScanner scanner;

	// configure the reader
	scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);

	myImage = new Image(width, height, "Y800", raw, width * height);

	// scan the image for barcodes
	numLines = scanner.scan(*myImage);
}

QRScanner::QRScanner(std::string path){
	if ( !boost::filesystem::exists( path ) )
	{
		std::cerr << "QRScanner: Can't read file: " << path  << std::endl;
	}
	else{
		CvMat *cv_matrix = cvLoadImageM(path.c_str(),CV_LOAD_IMAGE_GRAYSCALE); //"./debian.or.jp.qr.jpg"

		init((char*)cv_matrix->data.ptr,cv_matrix->width,cv_matrix->height);
	}

}



QRScanner::~QRScanner(){
	myImage->set_data(NULL, 0);
	delete myImage;
}


bool QRScanner::QRDetected(){
	return numLines>0;
}

string QRScanner::getQRCode()
{
    stringstream out;

    // extract results
    for(Image::SymbolIterator symbol = myImage->symbol_begin();
    		symbol != myImage->symbol_end();
    		++symbol) {
    	out << symbol->get_type_name() << symbol->get_data();
    	// do something useful with results
    	//cout << "decoded " << symbol->get_type_name()
        //     << " symbol \"" << symbol->get_data() << '"' << endl;
    }

    return  out.str();
}
#endif
