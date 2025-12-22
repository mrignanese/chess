CXX = g++
CXXFLAGS = -Wall -g -O0 -std=c++20
INCLUDE = $(shell pkg-config --cflags glfw3 glew glm) -Iinclude/ -Idependecies/
LDFLAGS = $(shell pkg-config --static --libs glfw3 glew) -lGL

SRC = $(wildcard src/*.cpp src/renderer/*.cpp dependecies/stb_image/stb_image.cpp \
                dependecies/imgui/*.cpp src/core/*.cpp src/game/*.cpp)

# objects go to build/
OBJ = $(patsubst %.cpp, build/%.o, $(SRC))

BIN = build/application

PCH = include/GLpch.h
PCH_GCH = build/GLpch.h.gch

# link step
$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $^ -o $@ $(LDFLAGS)

build/%.o: %.cpp $(PCH_GCH)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

# precompiled header
$(PCH_GCH): $(PCH)
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -x c++-header $(INCLUDE) $< -o $@

clean:
	rm -rf build
