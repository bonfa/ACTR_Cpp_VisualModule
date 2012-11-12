CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
MAIN_SRC := main.cpp
OCV_LIBS := `pkg-config opencv --libs`
OCV_PATH := `pkg-config opencv --cflags`
MY_LIB := launcher
LIBS_FLAGS := -L. -l$(MY_LIB) $(OCV_LIBS)
CC_FLAGS := -c -fPIC
AR_FLAGS := rcs
STATIC_LIB := lib$(MY_LIB).a
DYNAMIC_LIB := lib$(MY_LIB).dylib
CC := g++
EXEC := test

all: del_lib lib main

dyn: del_lib dyn_lib dyn_main set_lib_path

set_lib_path:
	export LD_LIBRARY_PATH=./

main:
	$(CC) $(MAIN_SRC) $(LIBS_FLAGS) -o $(EXEC)

lib: $(OBJ_FILES)
	ar $(AR_FLAGS) $(STATIC_LIB) $^

dyn_main:
	$(CC) $(MAIN_SRC) -L. -l$(MY_LIB) $(OCV_LIBS) -o $(EXEC)	

dyn_lib: $(OBJ_FILES)
	g++ -dynamiclib $(OCV_LIBS) -o $(DYNAMIC_LIB) -install_name ./$(DYNAMIC_LIB) $^

obj/%.o: src/%.cpp
	$(CC) $(OCV_PATH) $(CC_FLAGS) -o $@ $<

del_lib:
	rm -f $(STATIC_LIB) $(DYNAMIC_LIB)

clean:
	rm -f $(OBJ_FILES) $(STATIC_LIB) $(EXEC) libwrap.so libproxy.s proxy.lisp proxy-clos.lisp proxy_wrap.cxx
	
PROXY_LIBS= /opt/local/lib/libopencv_core.dylib /opt/local/lib/libopencv_highgui.dylib

mk_proxy: proxy_lib swig swig_lib

proxy.o:

proxy_lib:
	g++ -shared -fPIC -L. -llauncher $(OCV_LIBS) `pkg-config opencv --cflags` proxy.cpp -o libproxy.so

swig:
	swig -cffi -c++ proxy.i
	nano proxy_wrap.cxx

swig_lib:
	g++ -shared -fPIC -L. -llauncher $(OCV_LIBS) `pkg-config opencv --cflags` proxy_wrap.cxx -o libwrap.so
