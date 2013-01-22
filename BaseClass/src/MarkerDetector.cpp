#include "author.h"

#ifdef ENRICO

#define NO_IM


#include "MarkerDetector.h"


double 	vertex[4][2];
//std::vector<Quadrilateral> marker_list;
//Quadrilateral q1;

IplImage *image;
CvSize *size;
int channels, maxlength;
IplImage *m_pEdge;  // result of canny edge detection
IplImage *m_pGray;  // result of conversion to grayscale
IplImage *img;		// tmp prescale gray
IplImage *pyr;		// tmp afterscale gray
int canny_thres;
CvPoint myCenter;
ARUint8         *dataPtr;

typedef struct {
  char    *patt_name;
  int     patt_id;
  int     model_id;
  int     visible;
  double  width;
  double  center[2];
  double  trans[3][4];
} OBJECT_T;


OBJECT_T   object[2] = {
             {OBJ1_PATT_NAME, -1, OBJ1_MODEL_ID, 0, OBJ1_SIZE, {0.0,0.0}},
             {OBJ2_PATT_NAME, -1, OBJ2_MODEL_ID, 0, OBJ2_SIZE, {0.0,0.0}}
           };

/* set up the video format globals */

#ifdef _WIN32
char			*vconf = "Data\\WDM_camera_flipV.xml";
#else
//Variabile d'ambiente per usare la webcam, buildare le librerie con gstreamer, cambiare device=/dev/video0 in device=/dev/video1 per usare la seconda webcam
char			*vconf = "v4l2src device=/dev/video0 use-fixed-fps=false ! ffmpegcolorspace ! capsfilter caps=video/x-raw-rgb,bpp=24,width=640,height=480 ! identity name=artoolkit ! fakesink";
#endif

int             xsize, ysize;
int             thresh = 100;
int             ciunt = 0;

char           *cparam_name    = "Data/camera_para.dat";

ARParam         cparam;

static void   init(void);
static void   cleanup(void);
static void   keyEvent( unsigned char key, int x, int y);
static void   mainLoop(void);
static void   draw( int object, double trans[3][4] );

#ifdef STANDALONE
int main(int argc, char *argv[])
{
	#ifndef NO_IMG
	glutInit(&argc, argv);
	#endif
	startDetection();
	printf("Exiting\n");
	return (0);
}
#endif //STANDALONE



#ifdef STANDALONE
void startDetection(){
#else
void startDetection(){//boost::mutex& mutex){
	 //boost::mutex& mutex_;
	//mutex_= mutex;
	 
#endif //STANDALONE
	printf("Init ARToolkit stuff\n");
	int argc = 1;
	char *argv[] = {"./fake"};
	//char const*[]={"./fake"};
	glutInit(&argc, argv);
	init();
	printf("Setup done\n");
    arVideoCapStart();
    printf("Capture started\n");
    argMainLoop( NULL, keyEvent, mainLoop );

}

int stub(){
	return 2;	
}

static void   keyEvent( unsigned char key, int x, int y)
{
    /* quit if the ESC key is pressed */
    if( key == 0x1b ) {
        printf("*** %f (frame/sec)\n", (double)ciunt/arUtilTimer());
        cleanup();
        exit(0);
    }
}

std::vector<Quadrilateral *> getMarkers(){
	boost::mutex::scoped_lock lock(io_mutex);
	cvSetImageData( image, dataPtr, size->width * channels );
    cvSaveImage(IMG_PATH, image);
	return markersList;
	}

/* main loop */
static void mainLoop(void)
{

    ARMarkerInfo    *marker_info;
    int             marker_num;
    int             i, j, k;

    /* grab a vide frame */
    if( (dataPtr = (ARUint8 *)arVideoGetImage()) == NULL ) {
        arUtilSleep(2);
        return;
    }
    if( ciunt == 0 ) arUtilTimerReset();
    ciunt++;

	#ifndef NO_IMG
    argDrawMode2D();
    argDispImage( dataPtr, 0,0 );
	#endif

    /* detect the markers in the video frame */
    if( arDetectMarker(dataPtr, thresh, &marker_info, &marker_num) < 0 ) {
        cleanup();
        exit(0);
    }

	/** Prevents ArToolkit from grabbing next frame if the current frame needs to be written to file system */
    boost::mutex::scoped_lock lock(io_mutex);

    arVideoCapNext();

	#ifndef NO_IMG
    argDrawMode3D();
    argDraw3dCamera( 0, 0 );
    glClearDepth( 1.0 );
    glClear(GL_DEPTH_BUFFER_BIT);
	#endif
	
	markersList.clear();
	
    /* check for object visibility */
    for( i = 0; i < 2; i++ ) {
        k = -1;
        for( j = 0; j < marker_num; j++ ) {
            if( object[i].patt_id == marker_info[j].id ) {
                if( k == -1 ) k = j;
                else if( marker_info[k].cf < marker_info[j].cf ) k = j;
            }
        }
        object[i].visible = k;

        if( k >= 0 ) {
			//vertex = marker_info[k].vertex;
			
			//Lock to prevent race conditions while reading vertex from other threads
			
			memcpy(vertex, marker_info[k].vertex, sizeof (float) * 2 * 4); //2 colonne * 4 righe
			//markersList.push_back(new Quadrilateral(1,2, 4,6, 4,3, 2,7));
			//new Quadrilateral(1,2, 4,6, 4,3, 2,7);
			markersList.push_back(new Quadrilateral((int)(marker_info[k].vertex[0][0]),(int)(marker_info[k].vertex[0][1]), (int)(marker_info[k].vertex[1][0]),(int)(marker_info[k].vertex[1][1]), (int)(marker_info[k].vertex[2][0]),(int)(marker_info[k].vertex[2][1]), (int)(marker_info[k].vertex[3][0]),(int)(marker_info[k].vertex[3][1])));
			
			
			//vertex[0][0] = marker_info[k].vertex[0][0];
			//printf("Flottiamo %f\n", vertex[0][0]);
			//printf("Flottare %f\n", vertex[1][0]);
            arGetTransMat(&marker_info[k],
                          object[i].center, object[i].width,
                          object[i].trans);
			//printf("***(frame/sec)\n");
			
	#ifndef NO_IMG
            draw( object[i].model_id, object[i].trans );
	#endif
        }
    }
    lock.unlock();
    
    argSwapBuffers();

    if( object[0].visible >= 0
     && object[1].visible >= 0 ) {
        double  wmat1[3][4], wmat2[3][4];

        arUtilMatInv(object[0].trans, wmat1);
        arUtilMatMul(wmat1, object[1].trans, wmat2);

        for( j = 0; j < 3; j++ ) {
            for( i = 0; i < 4; i++ ) printf("%8.4f ", wmat2[j][i]);
            printf("\n");
        }
        printf("\n\n");
    }
}

static void init( void )
{
    ARParam  wparam;
    int      i;

    /* open the video path */
    if( arVideoOpen( vconf ) < 0 ) exit(0);
    /* find the size of the window */
    if( arVideoInqSize(&xsize, &ysize) < 0 ) exit(0);
    printf("Image size (x,y) = (%d,%d)\n", xsize, ysize);

    /* set the initial camera parameters */
    if( arParamLoad(cparam_name, 1, &wparam) < 0 ) {
        printf("Camera parameter load error !!\n");
        exit(0);
    }
    arParamChangeSize( &wparam, xsize, ysize, &cparam );
    arInitCparam( &cparam );
    printf("*** Camera Parameter ***\n");
    arParamDisp( &cparam );

    for( i = 0; i < 2; i++ ) {
        if( (object[i].patt_id=arLoadPatt(object[i].patt_name)) < 0 ) {
            printf("pattern load error: %s\n", object[i].patt_name);
            exit(0);
        }
    }

    /* open the graphics window */
    argInit( &cparam, 1.0, 0, 0, 0, 0 );

    //Opencv init
    m_pGray = m_pEdge = NULL;
    channels = 3;
    size = new CvSize();
    size->width = xsize;
    size->height = ysize;
    image = cvCreateImage(*size, IPL_DEPTH_8U, channels );
    //IplImage imagedf =  cvCreateImage(*size, IPL_DEPTH_8U, channels );

    canny_thres = 50;
    //cvInitImageHeader( image, *size, IPL_DEPTH_8U, channels );

    m_pGray = cvCreateImage( *size, IPL_DEPTH_8U , 1);
    int byte_per_pixel = (IPL_DEPTH_8U & 255) >> 3 ;
    img = cvCreateImage(	*size,
    		byte_per_pixel*8,
    		1 );

    pyr = cvCreateImage(	cvSize(size->width/2, size->height/2),
    		byte_per_pixel*8,
    		1 );
}

/* cleanup function called when program exits */
static void cleanup(void)
{
    arVideoCapStop();
    arVideoClose();
    argCleanup();
}

//disegna figure
static void draw( int object, double trans[3][4] )
{
    double    gl_para[16];
    GLfloat   mat_ambient[]     = {0.0, 0.0, 1.0, 1.0};
    GLfloat   mat_flash[]       = {0.0, 0.0, 1.0, 1.0};
    GLfloat   mat_flash_shiny[] = {50.0};
    GLfloat   light_position[]  = {100.0,-200.0,200.0,0.0};
    GLfloat   ambi[]            = {0.1, 0.1, 0.1, 0.1};
    GLfloat   lightZeroColor[]  = {0.9, 0.9, 0.9, 0.1};
    
    argDrawMode3D();
    argDraw3dCamera( 0, 0 );
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    
    /* load the camera transformation matrix */
    argConvGlpara(trans, gl_para);
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixd( gl_para );

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambi);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightZeroColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_flash);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_flash_shiny);	
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMatrixMode(GL_MODELVIEW);

    switch( object ) {
      case 0:
        glTranslatef( 0.0, 0.0, 25.0 );
        glutSolidCube(50.0);
        break;
      case 1:
        glTranslatef( 0.0, 0.0, 40.0 );
        glutSolidSphere(40.0, 24, 24);
        break;
      case 2:
        glutSolidCone(25.0, 100.0, 20, 24);
        break;
      default:
        glTranslatef( 0.0, 0.0, 10.0 );
        glutSolidTorus(10.0, 40.0, 24, 24);
        break;
    }

    glDisable( GL_LIGHTING );
    glDisable( GL_DEPTH_TEST );
}
#endif ENRICO
