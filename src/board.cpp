#include "board.hpp"

Board::Board() : startx(300), starty(100), blocksize(20), deltatime(250)
{
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            grid[i][j] = Block::Empty;
        }
    }

    currpiece = getRandomPiece();

    timer.restart();
}

sf::Color Board::getColorForBlock(Block block) const
{
    switch (block)
    {
    case Block::Empty:
        return sf::Color(0, 0, 0);
    case Block::Red:
        return sf::Color(180, 0, 0);
    case Block::Blue:
        return sf::Color(0, 0, 180);
    case Block::LightBlue:
        return sf::Color(0, 180, 180);
    case Block::Green:
        return sf::Color(0, 160, 0);
    case Block::Purple:
        return sf::Color(100, 0, 100);
    case Block::Yellow:
        return sf::Color(200, 200, 50);
    case Block::Orange:
        return sf::Color(200, 100, 0);
    default:
        return sf::Color::White;
    }
}

std::unique_ptr<Piece> Board::getRandomPiece() const
{
    int randnum = rand() % 7;
    switch (randnum)
    {
    case 0:
        return Piece::Factory::createIPiece();

    case 1:
        return Piece::Factory::createLPiece();

    case 2:
        return Piece::Factory::createJPiece();

    case 3:
        return Piece::Factory::createOPiece();

    case 4:
        return Piece::Factory::createSPiece();

    case 5:
        return Piece::Factory::createZPiece();

    case 6:
        return Piece::Factory::createTPiece();
    }

    throw std::runtime_error("How did you even manage this? rand() % 7 gave you a number that isn't an integer between 0 and 6 inclusive");
    return nullptr;
}

void Board::update()
{
    if (timer.getElapsedTime().asMilliseconds() >= deltatime)
    {
        for (int i = 0; i < 4; i++)
        {
            if ((currpiece->getGlobalPositions()[i].getRow() + 1 > 0) &&
                ((currpiece->getGlobalPositions()[i].getRow() == 19) ||
                 (grid[currpiece->getGlobalPositions()[i].getRow() + 1][currpiece->getGlobalPositions()[i].getCol()] != Block::Empty)))
            {
                for (int j = 0; j < 4; j++)
                {
                    grid[currpiece->getGlobalPositions()[j].getRow()][currpiece->getGlobalPositions()[j].getCol()] = currpiece->getColor();
                }

                currpiece = getRandomPiece();

                for (int j = 0; j < 20; j++)
                {
                    bool fullrow = true;
                    for (int k = 0; k < 10; k++)
                    {
                        if (grid[j][k] == Block::Empty)
                        {
                            fullrow = false;
                        }
                    }
                    if (fullrow)
                    {
                        for (int l = j; l > 0; l--)
                        {
                            for (int k = 0; k < 10; k++)
                            {
                                grid[l][k] = grid[l - 1][k];
                            }
                        }
                        for (int k = 0; k < 10; k++)
                        {
                            grid[0][k] = Block::Empty;
                        }
                    }
                }

                timer.restart();
                return;
            }
        }
        currpiece->moveDown();
        timer.restart();
    }
}

void Board::draw() const
{
    auto &window = WindowProvider::instance().getWindow();

    sf::RectangleShape tempblock;
    tempblock.setSize(sf::Vector2f(blocksize, blocksize));
    tempblock.setFillColor(sf::Color::Green);

    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            tempblock.setPosition(startx + j * blocksize, starty + i * blocksize);
            tempblock.setFillColor(getColorForBlock(grid[i][j]));
            window.draw(tempblock);
        }
    }
    for (int i = 0; i < 4; i++)
    {
        tempblock.setPosition(startx + currpiece->getGlobalPositions()[i].getCol() * blocksize,
                              starty + currpiece->getGlobalPositions()[i].getRow() * blocksize);
        tempblock.setFillColor(getColorForBlock(currpiece->getColor()));
        window.draw(tempblock);
    }
}

void Board::moveLeft()
{
    bool canMove = true;
    for (int i = 0; i < 4; i++)
    {
        if (currpiece->getGlobalPositions()[i].getCol() - 1 < 0 ||
            grid[currpiece->getGlobalPositions()[i].getRow()][currpiece->getGlobalPositions()[i].getCol() - 1] != Block::Empty)
        {
            canMove = false;
        }
    }
    if (canMove)
        currpiece->moveLeft();
}

void Board::moveRight()
{
    bool canMove = true;
    for (int i = 0; i < 4; i++)
    {
        if (currpiece->getGlobalPositions()[i].getCol() + 1 > 9 ||
            grid[currpiece->getGlobalPositions()[i].getRow()][currpiece->getGlobalPositions()[i].getCol() + 1] != Block::Empty)
        {
            canMove = false;
        }
    }
    if (canMove)
        currpiece->moveRight();
}

void Board::rotate()
{
    currpiece->rotateClockwise();
    bool undorot = false;
    for (int i = 0; i < 4; i++)
    {
        if (currpiece->getGlobalPositions()[i].getCol() > 9 || currpiece->getGlobalPositions()[i].getCol() < 0 ||
            currpiece->getGlobalPositions()[i].getRow() < 0 || currpiece->getGlobalPositions()[i].getRow() > 19 ||
            grid[currpiece->getGlobalPositions()[i].getRow()][currpiece->getGlobalPositions()[i].getCol()] != Block::Empty)
        {
            undorot = true;
        }
    }
    if (undorot)
        currpiece->rotateCounterClockwise();
}