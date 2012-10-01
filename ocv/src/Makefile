CC=g++
CFLAGS=`pkg-config opencv --cflags` 
LFLAGS=`pkg-config opencv --libs`
SOURCES=./ocv.cpp 
EXECUTABLE=ocv

all: tutorial
	
tutorial: $(OBJECTS) 
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(SOURCES) $(LFLAGS)

