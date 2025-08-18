CXX = g++
CXXFLAGS = -Wall -g -O0 -std=c++20
INCLUDE = $(shell pkg-config --cflags glfw3 glew glm) -Isrc/ -Isrc/renderer/include 
LDFLAGS = $(shell pkg-config --static --libs glfw3 glew) -lGL

SRC = $(wildcard src/*.cpp src/renderer/src/*.cpp src/stb_image/stb_image.cpp src/imgui/*.cpp)
BIN = build/main

$(BIN): $(SRC)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(SRC) -o $(BIN) $(LDFLAGS)

clean:
	rm -f $(BIN)