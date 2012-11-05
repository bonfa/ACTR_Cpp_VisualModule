CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
MAIN_SRC := main.cpp
LD_FLAGS := $(MAIN_SRC) -L. -llauncher -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_contrib -lopencv_legacy -lopencv_flann
CC_FLAGS := -c -fPIC
AR_FLAGS := rcs
STATIC_LIB := liblauncher.a
EXEC := test

all: lib main

main:
	g++ $(LD_FLAGS) -o $(EXEC)

lib: $(OBJ_FILES)
	ar $(AR_FLAGS) $(STATIC_LIB) $^

obj/%.o: src/%.cpp
	g++ -I/usr/include/opencv $(CC_FLAGS) -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_contrib -lopencv_legacy -lopencv_flann -c -o $@ $<

clean:
	rm -rf $(OBJ_FILES) $(STATIC_LIB) $(EXEC)