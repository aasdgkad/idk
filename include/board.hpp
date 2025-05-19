#pragma once
#include "windowprovider.hpp"
#include "piece.hpp"

class Board{
    private:
    Block grid[20][10];

    int startx, starty, blocksize, deltatime;
    sf::Clock timer;

    std::unique_ptr<Piece> currpiece;

    public:
    Board();
    ~Board() = default;
    Board(const Board &) = default;
    Board &operator=(const Board &) = default;

    void update();
    void draw() const;
    void moveLeft();
    void moveRight();
    void rotate();

    private:
    // Santa's little helpers
    sf::Color getColorForBlock(Block) const;
    std::unique_ptr<Piece> getRandomPiece() const;
};