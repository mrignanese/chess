CXX = g++
CXXFLAGS = -Wall -g -O0 -std=c++20
INCLUDE = $(shell pkg-config --cflags glfw3 glew glm) -Iinclude/ -Idependecies/
LDFLAGS = $(shell pkg-config --static --libs glfw3 glew) -lGL

SRC = $(wildcard src/*.cpp src/renderer/*.cpp dependecies/stb_image/stb_image.cpp \
		dependecies/imgui/*.cpp src/core/*.cpp src/game/*.cpp)
BIN = build/application

# pre compiled header
PCH = include/GL_pch.h
PCH_GCH = $(PCH).gch

#$(PCH_GCH): $(PCH)
#	$(CXX) $(CXXFLAGS) -x c++-header $(INCLUDE) $< -o $@

$(BIN): $(SRC)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(SRC) -o $(BIN) $(LDFLAGS)

clean:
	rm -f $(BIN)
	rm -f include/GL_pch.h.gch