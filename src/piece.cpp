#include "piece.hpp"

void Piece::moveLeft()
{
    for (int i = 0; i < 4; i++) {
        blocks[i].setCol(blocks[i].getCol() - 1);
    }
}

void Piece::moveRight()
{
    for (int i = 0; i < 4; i++) {
        blocks[i].setCol(blocks[i].getCol() + 1);
    }
}

void Piece::moveDown()
{
    for (int i = 0; i < 4; i++) {
        blocks[i].setRow(blocks[i].getRow() + 1);
    }
}

void Piece::rotateClockwise(){
    if(!canRotate)
        return;
    for(int i = 0; i < 4; i++){
        Position rel = blocks[i] - blocks[0];
        blocks[i] = blocks[0] + Position(-rel.getCol(),rel.getRow());
    }
}

void Piece::rotateCounterClockwise(){
    if(!canRotate)
        return;
    for(int i = 0; i < 4; i++){
        Position rel = blocks[i] - blocks[0];
        blocks[i] = blocks[0] + Position(rel.getCol(),-rel.getRow());
    }
}


std::unique_ptr<Piece> Piece::Factory::createLPiece() {
    std::array<Position, 4> blocks = {
        Position(-2, 4), Position(-1, 5),
        Position(-1, 4), Position(-3, 4)
    };

    return std::unique_ptr<Piece>(new Piece(blocks, Block::Orange, true));
}

std::unique_ptr<Piece> Piece::Factory::createIPiece() {
    std::array<Position, 4> blocks = {
        Position(-1, 4), Position(-1, 3),
        Position(-1, 5), Position(-1, 6)
    };

    return std::unique_ptr<Piece>(new Piece(blocks, Block::LightBlue, true));
}

std::unique_ptr<Piece> Piece::Factory::createOPiece() {
    std::array<Position, 4> blocks = {
        Position(-1, 4), Position(-1, 5),
        Position(-2, 4), Position(-2, 5)
    };

    return std::unique_ptr<Piece>(new Piece(blocks, Block::Yellow, false));
}

std::unique_ptr<Piece> Piece::Factory::createTPiece() {
    std::array<Position, 4> blocks = {
        Position(-1, 4), Position(-1, 3),
        Position(-1, 5), Position(-2, 4)
    };

    return std::unique_ptr<Piece>(new Piece(blocks, Block::Purple, true));
}

std::unique_ptr<Piece> Piece::Factory::createSPiece() {
    std::array<Position, 4> blocks = {
        Position(-1, 5), Position(-1, 4),
        Position(-2, 5), Position(-2, 6)
    };

    return std::unique_ptr<Piece>(new Piece(blocks, Block::Green, true));
}

std::unique_ptr<Piece> Piece::Factory::createZPiece() {
    std::array<Position, 4> blocks = {
        Position(-1, 5), Position(-1, 6),
        Position(-2, 4), Position(-2, 5)
    };

    return std::unique_ptr<Piece>(new Piece(blocks, Block::Red, true));
}

std::unique_ptr<Piece> Piece::Factory::createJPiece() {
    std::array<Position, 4> blocks = {
        Position(-1, 5), Position(-1, 4),
        Position(-2, 5), Position(-3, 5)
    };

    return std::unique_ptr<Piece>(new Piece(blocks, Block::Blue, true));
}
