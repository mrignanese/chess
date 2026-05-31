#pragma once

#include <string>

class Piece {
   public:
	Piece(const std::string& name);
	~Piece() = default;

	const std::string& GetName() const;

   private:
	std::string mName;
};
