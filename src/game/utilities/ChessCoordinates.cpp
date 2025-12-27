#include <string>

#include "game/utilities/ChessCoordinates.h"

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
