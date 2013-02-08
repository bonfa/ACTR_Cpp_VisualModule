#include "author.h"

#ifdef ENRICO

#define NO_IM


#include "MarkerDetector.h"
MarkerDetector* MarkerDetector::instance_ptr = 0;


//double 	vertex[4][2];
//std::vector<Quadrilateral> marker_list;
//Quadrilateral q1;

IplImage *image;
CvSize *size;
int channels;
cv::Mat *currentFrame;
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
#define XSIZE 1280
#define YSIZE 720
//Variabile d'ambiente per usare la webcam, buildare le librerie con gstreamer, cambiare device=/dev/video0 in device=/dev/video1 per usare la seconda webcam
string			vconf = "v4l2src device=/dev/video0 use-fixed-fps=false ! ffmpegcolorspace ! capsfilter caps=video/x-raw-rgb,bpp=24,width=" + XSIZE + ",height=" + YSIZE + "! identity name=artoolkit ! fakesink";



int             xsize, ysize;
int             thresh = 100;
int             ciunt = 0;

char           *cparam_name    = "Data/camera_para.dat";

ARParam         cparam;

static void   init(void);
static void   cleanup(void);
static void   keyEvent( unsigned char key, int x, int y);
static void   mainLoop(void);
static void   draw( int object, double trans[3][4], double vetrexes[4][2] );

static ARUint8		*gARTImage = NULL;
static ARUint8		*gARTsaveImage = NULL;

void startDetection(){//boost::mutex& mutex){

	printf("Init ARToolkit stuff\n");
	int argc = 1;
	char *argv[] = {"./fake"};
	//char const*[]={"./fake"};
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(XSIZE, YSIZE);

	//glutCreateWindow(argv[0]);
	// Setup argl library for current context.
	if ((gArglSettings = arglSetupForCurrentContext()) == NULL) {
		fprintf(stderr, "main(): arglSetupForCurrentContext() returned error.\n");
		exit(-1);
	}

	arMalloc(gARTsaveImage, ARUint8, XSIZE* YSIZE * AR_PIX_SIZE_DEFAULT);


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



int MarkerDetector::initMarkersData(){
	/** Use the lock to prevent race conditions */
	boost::mutex::scoped_lock lock(io_mutex);

	/** Copy the Quadrilateral list */
	slowMarkerList = std::vector<Quadrilateral*>(markersList.begin(),markersList.end());//markersList.

	/** Convert the current frame */
	cvSetImageData( image, dataPtr, size->width * channels );

	/** Copy current frame content in another variable */
	currentFrame = new cv::Mat(image, true);

	return 0;
}

cv::Mat * MarkerDetector::getFrame(){
	return currentFrame;
}

std::vector<Quadrilateral *> MarkerDetector::getMarkers(){
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
    std::vector<Quadrilateral *> backupList;
    try{
    	for(int i=0; i <markersList.size(); i++)
    		backupList.push_back(markersList.at(i));
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

    			arGetTransMatCont(&marker_info[k], object[i].trans, object[i].center, object[i].width, object[i].trans);

    			markersList.push_back(dynamic_cast<Quadrilateral*>(new Marker((int)(marker_info[k].vertex[0][0]*100/XSIZE),(int)(marker_info[k].vertex[0][1]*100/YSIZE), (int)(marker_info[k].vertex[1][0]*100/XSIZE),(int)(marker_info[k].vertex[1][1]*100/YSIZE), (int)(marker_info[k].vertex[2][0]*100/XSIZE),(int)(marker_info[k].vertex[2][1]*100/YSIZE), (int)(marker_info[k].vertex[3][0]*100/XSIZE),(int)(marker_info[k].vertex[3][1]*100/YSIZE), object[i].model_id, asin(object[i].trans[1][2]))));

#ifndef NO_IMG

    			draw( object[i].model_id, object[i].trans, marker_info[k].vertex );
#endif
    		}
    	}}
    catch(...){
    	markersList.clear();
    	for(int i=0; i <markersList.size(); i++)
    		markersList.push_back(backupList.at(i));
    }
    lock.unlock();

    argSwapBuffers();

    if( object[0].visible >= 0
    		&& object[1].visible >= 0 ) {
    	double  wmat1[3][4], wmat2[3][4];

    	arUtilMatInv(object[0].trans, wmat1);
    	arUtilMatMul(wmat1, object[1].trans, wmat2);
    }
}

static void init( void )
{
	ARParam  wparam;
    int      i;
    // Setup argl library for current context.
    	if ((gArglSettings = arglSetupForCurrentContext()) == NULL) {
    		fprintf(stderr, "main(): arglSetupForCurrentContext() returned error.\n");
    		exit(-1);
    	}

    /* open the video path */
    if( arVideoOpen( vconf.c_str() ) < 0 ) exit(0);
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
    channels = 3;
    size = new CvSize();
    size->width = xsize;
    size->height = ysize;
    image = cvCreateImage(*size, IPL_DEPTH_8U, channels );

}

/* cleanup function called when program exits */
static void cleanup(void)
{
    arVideoCapStop();
    arVideoClose();
    argCleanup();
}


static void endOrtho2D(void) {
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}


static void beginOrtho2D(int xsize, int ysize) {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, xsize, 0.0, ysize);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
}

void lineSeg(double x1, double y1, double x2, double y2, ARGL_CONTEXT_SETTINGS_REF contextSettings, ARParam cparam, double zoom)
{
	int enable;
    float   ox, oy;
    double  xx1, yy1, xx2, yy2;

	if (!contextSettings) return;
	arglDistortionCompensationGet(contextSettings, &enable);
    if (arglDrawModeGet(contextSettings) == AR_DRAW_BY_TEXTURE_MAPPING && enable) {
        xx1 = x1;  yy1 = y1;
        xx2 = x2;  yy2 = y2;
    } else {
        arParamIdeal2Observ(cparam.dist_factor, x1, y1, &xx1, &yy1);
        arParamIdeal2Observ(cparam.dist_factor, x2, y2, &xx2, &yy2);
    }

    xx1 *= zoom; yy1 *= zoom;
    xx2 *= zoom; yy2 *= zoom;

	ox = 0;
	oy = cparam.ysize - 1;
	glBegin(GL_LINES);
	glVertex2f(ox + xx1, oy - yy1);
	glVertex2f(ox + xx2, oy - yy2);
	glEnd();
    glFlush();
}

//disegna figure
static void draw( int object, double trans[3][4], double vertexes[4][2])
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
	glDrawBuffer(GL_BACK);

	arglDispImage(gARTImage, &cparam, 1.0, gArglSettings);	// zoom = 1.0.

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	beginOrtho2D(XSIZE, YSIZE);
	glLineWidth(4.0f);

	glColor3d(0.0, 1.0, 0.0);

	switch( object ) {
	case 0:
		glColor3d(0.0, 1.0, 0.0);
		break;
	case 1:
		glColor3d(1.0, 0.0, 0.0);
		break;
	case 2:
		glColor3d(0.0, 0.0, 1.0);
		break;
	default:
		glColor3d(0.5, 1.0, 0.2);
		break;
	}
	lineSeg(vertexes[0][0], vertexes[0][1],
			vertexes[1][0], vertexes[1][1], gArglSettings, cparam, 1.0);
	lineSeg(vertexes[3][0], vertexes[3][1],
			vertexes[0][0], vertexes[0][1], gArglSettings, cparam, 1.0);

	lineSeg(vertexes[1][0], vertexes[1][1],
			vertexes[2][0], vertexes[2][1], gArglSettings, cparam, 1.0);

	lineSeg(vertexes[2][0], vertexes[2][1],
			vertexes[3][0], vertexes[3][1], gArglSettings, cparam, 1.0);
	endOrtho2D();

	glutSwapBuffers();

	glDisable( GL_LIGHTING );
	glDisable( GL_DEPTH_TEST );
}
#endif //ENRICO
