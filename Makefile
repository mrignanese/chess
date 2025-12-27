########################################
### Basic Makefile concepts to know: ###
# 
# A Makefile rule looks like this -->
# target: dependencies
#	commands
#
# $@ refers to the target
# $^ refers to all dependencies
# $< refers to the first dependency
########################################

CXX = g++
CXX_FLAGS = -Wall -g -O0 -std=c++20
BUILD_DIR = ./build

INCLUDE = $(shell pkg-config --cflags glfw3 glew glm) -Iinclude/ -Idependecies/
LD_FLAGS = $(shell pkg-config --static --libs glfw3 glew) -lGL

SRC = $(wildcard src/*.cpp src/renderer/*.cpp dependecies/stb_image/stb_image.cpp \
        dependecies/imgui/*.cpp src/core/*.cpp src/game/*.cpp src/game/utilities/*.cpp)

# consider each .cpp file, and create corresponding .o file in build/
OBJ = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SRC))
BIN = $(BUILD_DIR)/chess

# default rule: build the binary
$(BIN): $(OBJ)
	$(CXX) $(CXX_FLAGS) $(INCLUDE) $^ -o $@ $(LD_FLAGS)

# rule to compile a single .cpp to .o
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXX_FLAGS) $(INCLUDE) -c $^ -o $@

# convenience rule to build .o files in current directory
%.o: $(BUILD_DIR)/%.o
	@true

clean:
	@find . -name "*.o" -delete
	@rm -f $(BIN)
	@rm -rf $(BUILD_DIR)
	@echo "Cleaned build files."
