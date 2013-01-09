INC_DIR= /usr/local/include/AR
LIB_DIR= /usr/local/lib
BIN_DIR= .

LDFLAG=-pthread -lgstreamer-0.10 -lgobject-2.0 -lgmodule-2.0 -lgthread-2.0 -lrt -lxml2 -lglib-2.0 -L/usr/X11R6/lib -L/usr/local/lib -L$(LIB_DIR)
LIBS= -lARgsub -lARvideo -lAR -lpthread -lglut -lGLU -lGL -lXi -lX11 -lm -pthread -lgstreamer-0.10 -lgobject-2.0 -lgmodule-2.0 -lgthread-2.0 -lrt -lxml2 -lglib-2.0
CFLAG= -O -pthread -I/usr/include/gstreamer-0.10 -I/usr/include/glib-2.0 -I/usr/lib/i386-linux-gnu/glib-2.0/include -I/usr/include/libxml2 -I/usr/X11R6/include -g -I$(INC_DIR)


all: $(BIN_DIR)/MarkerDetector

$(BIN_DIR)/MarkerDetector: MarkerDetector.o $(OBJS)
	cc -o $(BIN_DIR)/MarkerDetector MarkerDetector.o  $(LDFLAG) $(LIBS)

MarkerDetector.o: MarkerDetector.c 
	cc -c $(CFLAG) MarkerDetector.c

clean:
	rm -f *.o
	rm -f $(BIN_DIR)/MarkerDetector

allclean:
	rm -f *.o
	rm -f $(BIN_DIR)/MarkerDetector
	rm -f Makefile
