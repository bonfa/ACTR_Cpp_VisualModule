CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
MAIN_SRC := main.cpp
OCV_LIBS := -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_contrib -lopencv_legacy -lopencv_flann
OCV_PATH := -I/usr/include/opencv
MY_LIB := launcher
LD_FLAGS := $(MAIN_SRC) -L. -l$(MY_LIB) $(OCV_LIBS)
CC_FLAGS := -c -fPIC
AR_FLAGS := rcs
STATIC_LIB := lib$(MY_LIB).a
CC := g++
EXEC := test

all: lib main

main:
	$(CC) $(LD_FLAGS) -o $(EXEC)

lib: $(OBJ_FILES)
	ar $(AR_FLAGS) $(STATIC_LIB) $^

obj/%.o: src/%.cpp
	$(CC) $(OCV_PATH) $(CC_FLAGS) $(OCV_LIBS) -c -o $@ $<

clean:
	rm -f $(OBJ_FILES) $(STATIC_LIB) $(EXEC)