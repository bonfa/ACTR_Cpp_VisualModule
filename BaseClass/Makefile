CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
MAIN_SRC := main.cpp
OCV_LIBS := `pkg-config opencv --libs`
OCV_PATH := `pkg-config opencv --cflags`
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

obj/BaseClass.o: src/BaseClass.cpp 
	$(CC) $(OCV_PATH) $(CC_FLAGS) $(OCV_LIBS) -c -o $@ $<
	
obj/Launcher.o: src/Launcher.cpp 
	$(CC) $(OCV_PATH) $(CC_FLAGS) $(OCV_LIBS) -c -o $@ $<

obj/%.o: src/%.cpp
	$(CC) $(CC_FLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ_FILES) $(STATIC_LIB) $(EXEC)