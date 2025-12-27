#pragma once

#include <string>

std::pair<int, int> GetCoordinatesFromSquareName(const std::string& name);
std::string GetSquareNameFromCoordinates(int row, int col);
