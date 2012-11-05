CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
MAIN_SRC := main.cpp
LD_FLAGS := -static $(MAIN_SRC) -L. -llauncher
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
	g++ $(CC_FLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJ_FILES) $(STATIC_LIB) $(EXEC)