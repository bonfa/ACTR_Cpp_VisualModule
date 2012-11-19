#include <iostream>
#include <Magick++.h>
#include <zbar.h>

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv/cxcore.h>

using namespace std;
using namespace zbar;

int main (int argc, char **argv)
{
	CvMat *cv_matrix = cvLoadImageM("../debian.or.jp.qr.jpg",CV_LOAD_IMAGE_GRAYSCALE);
	int width = cv_matrix->width;
	int height= cv_matrix->height;
	char *raw = (char*)cv_matrix->data.ptr;

    // create a reader
    ImageScanner scanner;

    // configure the reader
    scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);

    // obtain image data
/*
    Magick::Image magick;  // read an image file
    //int width = magick.columns();   // extract dimensions
    //int height = magick.rows();
    Magick::Blob blob;              // extract the raw data
    magick.modifyImage();
    magick.write(&blob, "GRAY", 8);
    //const void *raw = blob.data();*/

    // wrap image data
    Image image(width, height, "Y800", raw, width * height);

    // scan the image for barcodes
    int n = scanner.scan(image);

    // extract results
    for(Image::SymbolIterator symbol = image.symbol_begin();
        symbol != image.symbol_end();
        ++symbol) {
        // do something useful with results
        cout << "decoded " << symbol->get_type_name()
             << " symbol \"" << symbol->get_data() << '"' << endl;
    }

    // clean up
    image.set_data(NULL, 0);

    return(0);
}


/*#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv/cxcore.h>
#include <iostream>
#include <zbar.h>

int main(){
	CvMat *cv_matrix = cvLoadImageM("/home/enrico/develop/cpp/BaseClass/debian.or.jp.qr.jpg",CV_LOAD_IMAGE_GRAYSCALE);
	int width = cv_matrix->width;
	int height= cv_matrix->height;
	char *raw = (char*)cv_matrix->data.ptr;

	ImageScanner scanner;
	scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);  
 
	Image image(width, height, "Y800", raw, width * height);
	int n = scanner.scan(image);

	for(Image::SymbolIterator symbol = image.symbol_begin();
        symbol != image.symbol_end();
        ++symbol) {
        // do something useful with results
        cout << "decoded " << symbol->get_type_name()
             << " symbol \"" << symbol->get_data() << '"' << endl;
    }
}*/
