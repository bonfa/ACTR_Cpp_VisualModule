CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
MAIN_SRC := main.cpp
OCV_LIBS := `pkg-config opencv --libs`
OCV_PATH := `pkg-config opencv --cflags`
MGK_PATH := `pkg-config --cflags Magick++`
MGK_LIBS := `pkg-config --libs Magick++`
ZBR_LIBS := /usr/local/lib/libzbar.dylib
JSN_LIBS := `pkg-config --libs jsoncpp`
JSN_PATH := `pkg-config --cflags jsoncpp`
BST_LIBS := -lboost_system -lboost_system-mt -pthread -lboost_thread

BST_PATH := -L/usr/local/lib 

QR_SOURCE := qr/main.cpp
QR_LIB := decodeqr
MY_LIB := launcher
LD_FLAGS := -L. $(BST_PATH) -l$(MY_LIB) $(JSN_PATH) $(JSN_LIBS) $(OCV_LIBS) $(OCV_PATH) $(BST_LIBS)
CC_FLAGS := -c -fPIC 
AR_FLAGS := rcs
STATIC_LIB := lib$(MY_LIB).a
DYNAMIC_LIB := lib$(MY_LIB).so
CC := g++
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
	$(CC) $(MAIN_SRC) $(LD_FLAGS) -o $(EXEC)

lib: $(OBJ_FILES)
	ar $(AR_FLAGS) $(STATIC_LIB) $^

dyn_main:
	$(CC) $(MAIN_SRC) $(LD_FLAGS) -o $(EXEC)	

dyn_lib: $(OBJ_FILES)
	$(CC) -shared $(OCV_LIBS) $(ZBR_LIBS) -o $(DYNAMIC_LIB) $^

obj/QRScanner.o: src/QRScanner.cpp
	$(CC) $(OCV_PATH) $(MGK_PATH) $(CC_FLAGS) -o $@ $<
	
obj/Server.o: src/Server.cpp
	$(CC) $(JSN_PATH) $(CC_FLAGS) -o $@ $<

obj/Session.o: src/Session.cpp
	$(CC) $(JSN_PATH) $(CC_FLAGS) -o $@ $<

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

