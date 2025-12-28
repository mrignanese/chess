#include <string>

#include "core/Mouse.h"
#include "core/Window.h"

std::pair<int, int> GetCoordinatesFromSquareName(const std::string& name) {
	// offset col and row so that 'a1' square is (0,0)
	int row = std::atoi(&name[1]) - 1;  // row 1 of chessboard is row 0
	int col = name[0] - 'a';            // column 'a' is column 0
	return {col, row};
}

std::string GetSquareNameFromCoordinates(int row, int col) {
	col += 97;  // 97 is ASCII code for 'a' (first column)
	row += 1;

	std::string colStr(reinterpret_cast<char*>(&col));
	std::string squareName = colStr + std::to_string(row);
	return squareName;
}

std::string GetSquareNameFromMousePosition(const Window& window) {
	// compute frame buffer height if window has been resized
	float squareSize = window.GetFrameBufferHeight() / 8;

	float x = Mouse::GetX();
	float y = Mouse::GetY();

	int row = y / squareSize;
	int col = x / squareSize;

	// origin is bottom-left corner in square coordinates,
	// but it is top-left corner in mouse coordinates. Therefore,
	// row coordinate is flipped when computing square name
	return GetSquareNameFromCoordinates(7 - row, col);
}
