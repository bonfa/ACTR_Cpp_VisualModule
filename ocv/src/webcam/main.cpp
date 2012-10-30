#include <opencv/cv.h>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include <opencv/cxcore.h>
#include <iostream>
// #include <math.h>
#include "LSWMS.h"

#define GOOD_RECTANGLE (0)
#define MAX_RECTCOUNT 2

using namespace cv;
using namespace std;

typedef struct _MarkerRectangle
{
	int MarkerID;//identifier
	CvPoint2D32f outer_corners[4];
	double outer_degrees[4];

	CvPoint2D32f inner_corners[4];
	double inner_degrees[4];

	CvPoint3D32f rotation_vector;
	CvPoint3D32f translation_vector;
	int Direction;


} MarkerRectangle;


 /** Function Headers */
 void detectFace( Mat color_img );
 IplImage* detectLines( Mat color_img , LSWMS lswms);
 Mat& IsolateColor(Mat& I);
 IplImage* FindRectangle(Mat colorImg, MarkerRectangle* rectangles,const int rectLimitCount);
 
 /** Global variables */
 CascadeClassifier face_cascade;
 MarkerRectangle markers[MAX_RECTCOUNT];
 
// Line segments (LSWMS and PPHT)
std::vector<LSEG> lSegs;
std::vector<double> errors;
cv::Size procSize;
// int numMaxLSegs = 0;
cv::Mat outputImg;

int main(int argc,char *argv[])
{
	
	//-- 1. Load the cascades
	if( !face_cascade.load( "/home/enrico/develop/cpp/ocv/src/webcam/haarcascade_frontalface_alt.xml" ) ){ printf("--(!)Error loading\n"); return -1; };
	
	int c;
	VideoCapture cap(0);
	if(!cap.isOpened())  // check if we succeeded
	  return -1;
// 	CvCapture* cv_cap = cvCreateCameraCapture(0);
	cvNamedWindow("Video",0); // create window
	cvNamedWindow("Face",0); // create window
	
	// Create and init LSWMS
	Mat frame;// = Mat(cvQueryFrame(cv_cap)); // get frame
	cap >> frame;
	procSize = cv::Size(frame.cols, frame.rows);
	LSWMS lswms(procSize, 3);
	
	for(;;) {
		cap >> frame;// = cvQueryFrame(cv_cap); // get frame
		 if( !frame.empty() )
		 {
// 		    FindRectangle(frame,markers,MAX_RECTCOUNT);
		    detectFace ( frame );
		    detectLines(frame,lswms);
		    imshow( "Video", frame ); //show the frame
		 }
			
		c = cvWaitKey(10); // wait 10 ms or for key stroke
		if(c == 27)
			break; // if ESC, break and quit
	}
	/* clean up */
// 	cvReleaseCapture( &cv_cap );
	cvDestroyWindow("Video");
	return 0;
}

IplImage* detectLines(Mat input, LSWMS lswms)
{
  lswms.run(input, lSegs, errors);
  lswms.drawLSegs(input, lSegs, errors);
}

/** @function detectAndDisplay */
void detectFace( Mat input )
{
  std::vector<Rect> faces;
  Mat frame_gray;
  
  cvtColor( input, frame_gray, CV_BGR2GRAY );
  equalizeHist( frame_gray, frame_gray );

  //-- Detect faces
  face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );
//   Mat asd;
    if(faces.size() <= 0 || faces[0].x + faces[0].width > 160 || faces[0].y + faces[0].height > 120) //if the face is not valid
    {}
    else
    {
      Mat roi (input, Rect(faces[0].x, faces[0].y, faces[0].width, faces[0].height) ); //isolate the face
      if( !roi.empty() )
      {
	imshow( "Face", roi ); //show the face in the second window
	Point center( faces[0].x + faces[0].width*0.5, faces[0].y + faces[0].height*0.5 ); //face center's coordinates
	ellipse( input, center, Size( faces[0].width*0.5, faces[0].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 ); //draw an ellipse on the frame
      }
    }
 }
 
 Mat& IsolateColor(Mat& I) //convert to green image
{
    // accept only char type matrices
    CV_Assert(I.depth() != sizeof(uchar));
    MatIterator_<Vec3b> it, end;
    for( it = I.begin<Vec3b>(), end = I.end<Vec3b>(); it != end; ++it)
    {
	(*it)[0] = 0; //blue channel
	(*it)[2] = 0; //red channel
    }

    return I;
}

// IplImage* FindRectangle(Mat colorImg, MarkerRectangle* rectangles,const int rectLimitCount)
// {
// 	int i;
// 	int r;
// 
// 	//create storage for contours
// 	CvMemStorage *storage;
// 	CvMemStorage *storagepoly;
// 	CvSeq *firstcontour=NULL;
// 	CvSeq *polycontour=NULL;
// 	Mat gsImage;
// // 	int contourCount=0;
// 
// 	CvSeq* c;
// 	char text[4];
// 
// 	int detectedRectCount=0;
// 	int res=0;
// 	CvSeq* c_vnext;
// 
// 
// 	//initialize rectangles
// 	for(i=0;i<rectLimitCount;i++)
// 	{
// 		rectangles[i].MarkerID=-1;
// 		for (r=0;r<4;r++)
// 		{
// 			rectangles[i].outer_corners[r]=cvPoint2D32f(-1,-1);
// 			rectangles[i].outer_degrees[r]=-1;
// 
// 			rectangles[i].inner_corners[r]=cvPoint2D32f(-1,-1);
// 			rectangles[i].inner_degrees[r]=-1;
// 			rectangles[i].rotation_vector=cvPoint3D32f(0,0,0);
// 			rectangles[i].translation_vector=cvPoint3D32f(0,0,0);
// 		}
// 	}
// 
// 
// 	storage = cvCreateMemStorage (0);//original contours
// 	storagepoly = cvCreateMemStorage (0);//polygon approximated contour
// 	cvClearMemStorage(storage);
// 	cvClearMemStorage(storagepoly);	
// 
// 	gsImage=cvCreateImage(cvGetSize(colorImg),IPL_DEPTH_8U,1);
// 
// 	//convert to grayscale
// 	cvCvtColor(colorImg,gsImage,CV_BGR2GRAY);
// 	//Convert gray to binary
// 	cvThreshold (gsImage, gsImage, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
// 	cvNot(gsImage,gsImage);	
// 	findContours (gsImage, storage, CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE);
// 
// 	//Approximate to polygon
// 	polycontour=cvApproxPoly(firstcontour,sizeof(CvContour),storagepoly,CV_POLY_APPROX_DP,4,1);
// 	approxPolyDP(firstcontour, );
// 
// 	for(c=polycontour;c!=NULL;c=c->h_next)
// 	{ 
// 		int res;
// 		
// 		//ignore
// 		if(detectedRectCount==rectLimitCount) continue;
// 		//ignore too long or too short contours.
// 		if(cvContourPerimeter(c)>(colorImg->width+colorImg->height)*1.8)
// 		  continue;
// 
// 		if(cvContourPerimeter(c)<50)
// 		  continue;
// 		//ignore conercount!=4
// 		if(c->total!=4)
// 		  continue;
// 		// ignore v_next contour is null or v_next is not rectangle
// 		if(NULL==c->v_next)
// 		  continue;
// 		if(4!=c->v_next->total)
// 		  continue;
// 		
// 		res=0;
// 		c_vnext=c->v_next;
// // 		res=CheckRectangle(c,c_vnext,&rectangles[detectedRectCount]);
// 
// // 		if(GOOD_RECTANGLE==res)
// // 		{
// 			//Draw marker's contour
// 			detectedRectCount++;
// 			cvDrawContours(colorImg,c,CV_RGB(255,0,0),CV_RGB(0,0,0),0,3,8,cvPoint(0,0));
// 			cvDrawContours(colorImg,c_vnext,CV_RGB(0,255,0),CV_RGB(0,255,255),0,2,8,cvPoint(0,0));
// // 		}
// 	}
// 	cvReleaseMemStorage(&storage);
// 	cvReleaseMemStorage(&storagepoly);
// 	cvReleaseImage(&gsImage);
// 	
// 	return colorImg;
// 
// }
