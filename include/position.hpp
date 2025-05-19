#pragma once

class Position {
private:
    int row;
    int col;

public:
    Position(int r = 0, int c = 0) noexcept : row(r), col(c) {}
    Position(const Position& other) noexcept = default;
    Position& operator=(const Position& rhs) noexcept = default;

    inline int getRow() const noexcept { return row; }
    inline int getCol() const noexcept { return col; }

    inline void setRow(int r) noexcept { row = r; }
    inline void setCol(int c) noexcept { col = c; }

    inline Position operator+(const Position& other) const noexcept {
        return Position(row + other.row, col + other.col);
    }
    inline Position operator-(const Position& other) const noexcept {
        return Position(row - other.row, col - other.col);
    }
    inline Position& operator+=(const Position& other) noexcept {
        row += other.row;
        col += other.col;
        return *this;
    }
    inline Position& operator-=(const Position& other) noexcept {
        row -= other.row;
        col -= other.col;
        return *this;
    }
    inline bool operator==(const Position& other) const noexcept {
        return row == other.row && col == other.col;
    }
    inline bool operator!=(const Position& other) const noexcept {
        return !(*this == other);
    }
};
