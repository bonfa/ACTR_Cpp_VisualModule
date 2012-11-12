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
#include <opencv/highgui.h>
#include <opencv/cxcore.h>
#include <iostream>

#include <decodeqr.h>

void qr_dec() {
	printf("libdecodeqr version %s\n", qr_decoder_version());
	cvNamedWindow("src", 1);

	IplImage* src = cvLoadImage("./debian.or.jp.qr.jpg", 1);
	cvShowImage("src", src);
	//
	// initialize
	//
	QrDecoderHandle decoder = qr_decoder_open();
	//
	// do decode using default parameter
	//
	short stat = qr_decoder_decode_image(decoder, src);
	printf("STATUS=%04x\n", stat);
	//
	// get QR code header
	//
	QrCodeHeader header;
	if (qr_decoder_get_header(decoder, &header)) {
		//
		// get QR code text
		// To null terminate, a buffer size is larger than body size.
		//
		char* buf = new char[header.byte_size + 1];
		qr_decoder_get_body(decoder, (unsigned char*) (buf),
				header.byte_size + 1);
		printf("Contenuto del QR: %s\n", buf);
	}
	//
	// finalize
	//
	qr_decoder_close(decoder);
	puts("");
	puts("Hit any key to end.");
	cvWaitKey(0);
	cvDestroyAllWindows();
	cvReleaseImage(&src);
}

int cam(){
	int show_bin_image=0;


	    //
	    // start camera
	    //
	    CvCapture *capture=cvCaptureFromCAM(0);
	    if(!capture)
	        return(-1);

	    //
	    // initialize qr decoder
	    //
	    QrDecoderHandle decoder=qr_decoder_open();
	    printf("libdecodeqr version %s\n",qr_decoder_version());


	    cvNamedWindow("src",1);

	    if(show_bin_image)
	        cvNamedWindow("bin",1);

	    puts("Hit [SPACE] key to grab, or any key to end.");
	    puts("");

	    //
	    // 1 shot grabing
	    //
	    //
	    // allocate grabed buffer to decoder
	    //
	    int key=-1;

	    IplImage *camera=cvQueryFrame(capture);
	    IplImage *src=NULL,*bin=NULL;
	    if(camera){
	        src=cvCloneImage(camera);
	        qr_decoder_set_image_buffer(decoder,src);
	    }
	    else
	        key=1;

	    unsigned char *text=NULL;
	    int text_size=0;

	    while(key<=0){
	        cvShowImage("src",camera);
	        key=cvWaitKey(150);

	        //
	        // when [SPACE] key pressed, do decode.
	        //
	        if(key==0x20&&!qr_decoder_is_busy(decoder)){
	            key=-1;

	            //
	            // if left-bottom origin (MS-Windows style) format,
	            // it must be converted to left-top origin.
	            //
	            if(camera->origin)
	                cvConvertImage(camera,src,CV_CVTIMG_FLIP);
	            else
	                cvCopy(camera,src);

	            //
	            // While decoding is a failure, decrease the
	            // adaptive_th_size parameter.
	            // Note that the adaptive_th_size must be odd.
	            //
	            short sz,stat;
	            for(sz=25,stat=0;
	                (sz>=3)&&((stat&QR_IMAGEREADER_DECODED)==0);
	                sz-=2)
	                stat=qr_decoder_decode(decoder,sz);

	            //
	            // for debug, show binarized image.
	            //
	            if(bin)
	                cvReleaseImage(&bin);
	            if(show_bin_image){
	                bin=cvCloneImage(qr_decoder_get_binarized_image_buffer(decoder));
	                cvShowImage("bin",bin);
	            }
	            printf("adaptive_th_size=%d, status=%04x\n",sz,stat);

	            //
	            // on suceed decoding, print decoded text.
	            //
	            QrCodeHeader header;
	            if(qr_decoder_get_header(decoder,&header)){
	                if(text_size<header.byte_size+1){
	                    if(text)
	                        delete text;

	                    text_size=header.byte_size+1;
	                    text=new unsigned char[text_size];
	                }
	                qr_decoder_get_body(decoder,text,text_size);
	                printf("%s\n\n",text);

	                //
	                // draw found code region with green line
	                //
	                CvPoint *vertexes=qr_decoder_get_coderegion_vertexes(decoder);
	                CvPoint pt=vertexes[3];
	                int i;
	                for(i=0;i<4;i++){
	                    cvLine(src,pt,vertexes[i],CV_RGB(0,255,0),3);
	                    pt=vertexes[i];
	                }

	                //
	                // draw found finder patterns with green ellipse
	                //
	                CvBox2D *boxes=qr_decoder_get_finderpattern_boxes(decoder);
	                for(i=0;i<3;i++){
	                    CvSize sz=cvSize((int)boxes[i].size.width/2,
	                                     (int)boxes[i].size.height/2);
	                    cvEllipse(src,
	                              cvPointFrom32f(boxes[i].center),
	                              sz,
	                              boxes[i].angle,
	                              0,360,
	                              CV_RGB(0,255,0),2);
	                }

	                if(src->origin)
	                    cvConvertImage(src,src,CV_CVTIMG_FLIP);

	                cvShowImage("src",src);

	                //
	                // wait 1500msec.
	                //
	                key=cvWaitKey(1500);
	            }
	        }

	        camera=cvQueryFrame(capture);
	        if(!camera)
	            break;
	    }

	    if(text)
	        delete text;

	    qr_decoder_close(decoder);
	    if(bin)
	        cvReleaseImage(&bin);
	    if(src)
	        cvReleaseImage(&src);

	    cvReleaseCapture(&capture);

	    return 0;
}

int launch(){
	Button * b = new Button(10,2,20,20,"ciao");
	Circle * c = new Circle(8, 10, 15);
	Quadrilateral * q = new Quadrilateral(1,22,31,4,53,6,37,855);
	Triangle * t = new Triangle(0,1,22,3,43,51);

	std::cout << "Launcher\n";

	std::cout << b->getChunk();
	std::cout << c->getChunk();
	std::cout << q->getChunk();

	std::cout << t->getChunk();

	Object * o = c;

	std::cout << o->getChunk();

	BaseClass *ba = new BaseClass();

	qr_dec();

	int show_bin_image=0;




	    //
	    // start camera
	    //
	    CvCapture *capture=cvCaptureFromCAM(0);
	    if(!capture)
	        return(-1);

	    //
	    // initialize qr decoder
	    //
	    QrDecoderHandle decoder=qr_decoder_open();
	    printf("libdecodeqr version %s\n",qr_decoder_version());


	    cvNamedWindow("src",1);

	    if(show_bin_image)
	        cvNamedWindow("bin",1);

	    puts("Hit [SPACE] key to grab, or any key to end.");
	    puts("");

	    //
	    // 1 shot grabing
	    //
	    //
	    // allocate grabed buffer to decoder
	    //
	    int key=-1;

	    IplImage *camera=cvQueryFrame(capture);
	    IplImage *src=NULL,*bin=NULL;
	    if(camera){
	        src=cvCloneImage(camera);
	        qr_decoder_set_image_buffer(decoder,src);
	    }
	    else
	        key=1;

	    unsigned char *text=NULL;
	    int text_size=0;

	    while(key<=0){
	        cvShowImage("src",camera);
	        key=cvWaitKey(150);

	        //
	        // when [SPACE] key pressed, do decode.
	        //
	        if(key==0x20&&!qr_decoder_is_busy(decoder)){
	            key=-1;

	            //
	            // if left-bottom origin (MS-Windows style) format,
	            // it must be converted to left-top origin.
	            //
	            if(camera->origin)
	                cvConvertImage(camera,src,CV_CVTIMG_FLIP);
	            else
	                cvCopy(camera,src);

	            //
	            // While decoding is a failure, decrease the
	            // adaptive_th_size parameter.
	            // Note that the adaptive_th_size must be odd.
	            //
	            short sz,stat;
	            for(sz=25,stat=0;
	                (sz>=3)&&((stat&QR_IMAGEREADER_DECODED)==0);
	                sz-=2)
	                stat=qr_decoder_decode(decoder,sz);

	            //
	            // for debug, show binarized image.
	            //
	            if(bin)
	                cvReleaseImage(&bin);
	            if(show_bin_image){
	                bin=cvCloneImage(qr_decoder_get_binarized_image_buffer(decoder));
	                cvShowImage("bin",bin);
	            }
	            printf("adaptive_th_size=%d, status=%04x\n",sz,stat);

	            //
	            // on suceed decoding, print decoded text.
	            //
	            QrCodeHeader header;
	            if(qr_decoder_get_header(decoder,&header)){
	                if(text_size<header.byte_size+1){
	                    if(text)
	                        delete text;

	                    text_size=header.byte_size+1;
	                    text=new unsigned char[text_size];
	                }
	                qr_decoder_get_body(decoder,text,text_size);
	                printf("%s\n\n",text);

	                //
	                // draw found code region with green line
	                //
	                CvPoint *vertexes=qr_decoder_get_coderegion_vertexes(decoder);
	                CvPoint pt=vertexes[3];
	                int i;
	                for(i=0;i<4;i++){
	                    cvLine(src,pt,vertexes[i],CV_RGB(0,255,0),3);
	                    pt=vertexes[i];
	                }

	                //
	                // draw found finder patterns with green ellipse
	                //
	                CvBox2D *boxes=qr_decoder_get_finderpattern_boxes(decoder);
	                for(i=0;i<3;i++){
	                    CvSize sz=cvSize((int)boxes[i].size.width/2,
	                                     (int)boxes[i].size.height/2);
	                    cvEllipse(src,
	                              cvPointFrom32f(boxes[i].center),
	                              sz,
	                              boxes[i].angle,
	                              0,360,
	                              CV_RGB(0,255,0),2);
	                }

	                if(src->origin)
	                    cvConvertImage(src,src,CV_CVTIMG_FLIP);

	                cvShowImage("src",src);

	                //
	                // wait 1500msec.
	                //
	                key=cvWaitKey(1500);
	            }
	        }

	        camera=cvQueryFrame(capture);
	        if(!camera)
	            break;
	    }

	    if(text)
	        delete text;

	    qr_decoder_close(decoder);
	    if(bin)
	        cvReleaseImage(&bin);
	    if(src)
	        cvReleaseImage(&src);

	    cvReleaseCapture(&capture);

	imshow("finestra",ba->getImage("./lena.jpg"));
	waitKey(0);

	VideoCapture cap = ba->getStream();
	ba->showVideo(cap);


	return 0;

}


