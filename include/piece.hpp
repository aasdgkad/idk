#pragma once

#include <array>
#include <memory>
#include "position.hpp"

enum class Block{
    Empty,
    Red,
    Blue,
    LightBlue,
    Green,
    Purple,
    Yellow,
    Orange
};

class Piece
{
private:
    Piece(std::array<Position, 4> blocks, Block color, bool canRotate) : blocks(blocks), color(color), canRotate(canRotate) {}
    Piece() = default;
    Piece(const Piece &) = default;
    Piece &operator=(const Piece &) = default;

public:
    ~Piece() = default;

    void moveLeft();
    void moveRight();
    void moveDown();

    inline const std::array<Position, 4> &getGlobalPositions() const noexcept { return blocks; }
    inline Block getColor() const noexcept { return color; }

    void rotateClockwise();
    void rotateCounterClockwise();

private:
    std::array<Position, 4> blocks;
    Block color;
    bool canRotate;


public:
class Factory {
    public:
        Factory() = delete;
        Factory(const Factory&) = delete;
        Factory& operator=(const Factory&) = delete;

        static std::unique_ptr<Piece> createLPiece();
        static std::unique_ptr<Piece> createIPiece();
        static std::unique_ptr<Piece> createOPiece();
        static std::unique_ptr<Piece> createTPiece();
        static std::unique_ptr<Piece> createSPiece();
        static std::unique_ptr<Piece> createZPiece();
        static std::unique_ptr<Piece> createJPiece();
    };

    friend class Factory;
};