#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
using namespace cv;

int main(int argc, char *argv[])
{
  IplImage* img = 0;

  img=cvLoadImage("./lena.jpg");     // carica l'immagine

  cvNamedWindow("mainWin", CV_WINDOW_AUTOSIZE);       // crea la finestra

  cvShowImage("mainWin", img );    //  mostra l'immagine

  cvWaitKey(0);    // wait for a key

  cvReleaseImage(&img );    //rilascia l'immagine

  system("PAUSE");
  return 0;
}

