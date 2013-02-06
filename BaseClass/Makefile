DEBUG := -g

#OS detection
UNAME := $(shell uname -s)

CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
MAIN_SRC := main.cpp
OCV_LIBS := `pkg-config opencv --libs`
ifeq ($(UNAME), Linux)
OCV_PATH := `pkg-config opencv --cflags` -I/usr/include/opencv2
endif
ifeq ($(UNAME), Darwin)
OCV_PATH := `pkg-config opencv --cflags` -I/opt/local/include/opencv2
endif
MGK_PATH := `pkg-config --cflags Magick++`
MGK_LIBS := `pkg-config --libs Magick++`
#ZBR_LIBS := `pkg-config --libs zbar`
## Verificare che vada bene anche in ufficio
ifeq ($(UNAME), Linux)
ZBR_LIBS := `pkg-config --libs zbar`
ZBR_PATH := -I/usr/lib/
endif
ifeq ($(UNAME), Darwin)
ZBR_LIBS := /opt/local/lib/libzbar.dylib
ZBR_PATH := -I/opt/local/include/
endif
ifeq ($(UNAME), Linux)
JSN_LIBS := `pkg-config --libs jsoncpp`
JSN_PATH := `pkg-config --cflags jsoncpp`
endif
ifeq ($(UNAME), Darwin)
JSN_LIBS := /opt/local/lib/libjson_linux-gcc-4.2.1_libmt.dylib
JSN_PATH := -I/opt/local/include/json
endif
ifeq ($(UNAME), Linux)
BST_LIBS := -L/usr/local/lib -lboost_system -lboost_system-mt -pthread -lboost_thread -lboost_filesystem
BST_PATH := -I/usr/local/include/boost
endif
ifeq ($(UNAME), Darwin)
BST_LIBS := -L/opt/local/lib -lboost_system-mt -pthread -lboost_thread-mt -lboost_filesystem-mt
BST_PATH := -I/opt/local/include/boost 
endif

ifeq ($(UNAME), Linux)
ART_FLAGS := -pthread -lgstreamer-0.10 -lgobject-2.0 -lgmodule-2.0 -lgthread-2.0 -lrt -lxml2 -lglib-2.0 $(OCV_LIBS) -L/usr/X11R6/lib -L/usr/local/lib
ART_LIBS= -lARgsub -lARvideo -lAR -lARgsub_lite -lpthread -lglut -lGLU -lGL -lXi -lX11 -lm -pthread -lgstreamer-0.10 -lgobject-2.0 -lgmodule-2.0 -lgthread-2.0 -lrt -lxml2 -lglib-2.0
ART_CFLAG = -O -pthread $(OCV_PATH) -I/usr/include/gstreamer-0.10 -I/usr/include/glib-2.0 -I/usr/lib/i386-linux-gnu/glib-2.0/include -I/usr/include/libxml2 -I/usr/X11R6/include -g -I/usr/local/include/AR
endif
ifeq ($(UNAME), Darwin)
ART_FLAGS := -lgstreamer-0.10 -lgobject-2.0 -lgmodule-2.0 -lgthread-2.0 -lxml2 -lglib-2.0 -L/usr/X11R6/lib
ART_LIBS := -L/Users/stefano/Downloads/ARToolKit/lib/ -lARgsub -lARvideo -lAR -lARgsub_lite #-lpthread -lglut -lGLU -lGL -lXi -lX11 -lm -pthread -lgstreamer-0.10 -lgobject-2.0 -lgmodule-2.0 -lgthread-2.0 -lrt -lxml2 -lglib-2.0
#ART_PATH := 
ART_CFLAG := -O -pthread -I/opt/local/include/gstreamer-0.10 -I/opt/local/include/glib-2.0 -I/opt/local/lib/i386-linux-gnu/glib-2.0/include -I/opt/local/include/libxml2 -I/Opt/local/X11R6/include -g -I/Users/stefano/Downloads/ARToolKit/include
endif

QR_SOURCE := qr/main.cpp
QR_LIB := decodeqr
MY_LIB := launcher
LD_FLAGS := -L. $(BST_PATH) -l$(MY_LIB) $(JSN_LIBS) $(OCV_LIBS) $(OCV_PATH) $(BST_LIBS) $(MGK_LIBS) $(ZBR_LIBS) #$(ART_FLAGS) $(ART_LIBS) $(ART_CFLAG)
CC_FLAGS := -c -fPIC
AR_FLAGS := rcs
STATIC_LIB := lib$(MY_LIB).a
DYNAMIC_LIB := lib$(MY_LIB).so
CC := g++ $(DEBUG)
EXEC := test
SCAN := scan_image

ifeq ($(mode),debug)
   CC := $(CC) -g -Wall
endif

all: del_lib lib main

dyn: del_lib dyn_lib dyn_main set_lib_path

set_lib_path:
	export LD_LIBRARY_PATH=./

main:
	$(CC) $(MGK_PATH)  $(ZBR_PATH) $(MAIN_SRC) $(LD_FLAGS) -o $(EXEC)

lib: $(OBJ_FILES)
	ar $(AR_FLAGS) $(STATIC_LIB) $^

dyn_main:
	$(CC) $(MAIN_SRC) $(LD_FLAGS) -o $(EXEC)	

dyn_lib: $(OBJ_FILES)
	$(CC) -shared $(OCV_LIBS) $(ZBR_LIBS) -o $(DYNAMIC_LIB) $^

obj/QRScanner.o: src/QRScanner.cpp
	$(CC) $(OCV_PATH) $(MGK_PATH) $(ZBR_PATH) $(CC_FLAGS) -o $@ $<
	
obj/Server.o: src/Server.cpp
	$(CC) $(OCV_PATH) $(JSN_PATH) $(MGK_PATH) $(ZBR_PATH) $(CC_FLAGS) $(ART_CFLAG) -o $@ $<

obj/Session.o: src/Session.cpp
	echo "Compilo il Session"	
	$(CC) $(OCV_PATH) $(JSN_PATH) $(MGK_PATH) $(ZBR_PATH) $(CC_FLAGS) $(ART_CFLAG) -o $@ $<
	
obj/MarkerDetector.o: src/MarkerDetector.cpp
	$(CC)  $(CC_FLAGS) $(OCV_PATH) $(ART_CFLAG) -Wno-write-strings -o $@ $<

obj/FeatureExtractor.o: src/FeatureExtractor.cpp
	$(CC) $(OCV_PATH) $(MGK_PATH) $(JSN_PATH)  $(ZBR_PATH) $(CC_FLAGS) $(ART_CFLAG) -o $@ $<
	
obj/FeatureGetter.o: src/FeatureGetter.cpp
	$(CC) $(OCV_PATH) $(MGK_PATH) $(JSN_PATH)  $(ZBR_PATH) $(CC_FLAGS) $(ART_CFLAG) -o $@ $<

obj/proxy.o: src/proxy.cpp
	$(CC) $(OCV_PATH) $(MGK_PATH) $(JSN_PATH) $(CC_FLAGS) $(ART_CFLAG) -o $@ $<
	
obj/%.o: src/%.c
	$(CC) $(ART_CFLAG) $(OCV_PATH)  $(CC_FLAGS) -o $@ $<
	
obj/%.o: src/%.cpp
	$(CC) $(OCV_PATH)  $(CC_FLAGS) -o $@ $<

del_lib:
	rm -f $(STATIC_LIB) $(DYNAMIC_LIB)

clean:
	rm -f $(OBJ_FILES) $(STATIC_LIB) $(EXEC) $(SCAN) libwrap.so libproxy.so proxy.lisp proxy-clos.lisp proxy_wrap.cxx

run_image: image
	./qr/$(SCAN) ./debian.or.jp.qr.jpg

image:
	$(CC) $(MGK_PATH) $(OCV_PATH)  -o $(SCAN) $(QR_SOURCE) $(OCV_LIBS) $(MGK_LIBS) $(ZBR_LIBS)

mk_proxy: proxy_lib swig swig_lib

proxy.o:

proxy_lib:
	g++ -shared -fPIC -L. -llauncher $(OCV_LIBS) `pkg-config opencv --cflags` proxy.cpp -o libproxy.so

swig:
	swig -cffi -c++ proxy.i
	nano proxy_wrap.cxx

swig_lib:
	g++ -shared -fPIC -L. -llauncher $(OCV_LIBS) `pkg-config opencv --cflags` proxy_wrap.cxx -o libwrap.so

