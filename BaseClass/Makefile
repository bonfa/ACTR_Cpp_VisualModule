CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
MAIN_SRC := main.cpp
OCV_LIBS := `pkg-config opencv --libs`
OCV_PATH := `pkg-config opencv --cflags`
MY_LIB := launcher
LD_FLAGS := -L. -l$(MY_LIB) $(OCV_LIBS)
CC_FLAGS := -c -fPIC
AR_FLAGS := rcs
STATIC_LIB := lib$(MY_LIB).a
DYNAMIC_LIB := lib$(MY_LIB).so
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
	$(CC) $(MAIN_SRC) $(LD_FLAGS) -o $(EXEC)	

dyn_lib: $(OBJ_FILES)
	g++ -shared $(OCV_LIBS) -o $(DYNAMIC_LIB) $^


obj/%.o: src/%.cpp
	$(CC) $(OCV_PATH) $(CC_FLAGS) -o $@ $<

del_lib:
	rm -f $(STATIC_LIB) $(DYNAMIC_LIB)

clean:
	rm -f $(OBJ_FILES) $(STATIC_LIB) $(EXEC)