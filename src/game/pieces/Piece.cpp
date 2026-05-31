#include "game/pieces/Piece.h"

Piece::Piece(const std::string& name): mName(name) {

}

const std::string& Piece::GetName() const {
    return mName;
}
