#pragma once

#include <iostream>
#include <array>
#include <deque>
#include "Coord.hpp"

typedef std::deque<Coord> SnakeBody;

class Board
{
public:
    static const unsigned BOARD_HEIGHT = 10;
    static const unsigned BOARD_WIDTH = 20;

    void printBoard();
    void putSnake(const SnakeBody& snake);
    void initializeBoard();
    bool appleFound(Coord where);
    bool checkAvailability(Coord where);
    void clearCell(Coord where);
    void setApple(Coord where);
    void setWall(Coord where);

private:
    typedef std::array<std::array<char, BOARD_WIDTH>, BOARD_HEIGHT> GameBoardArray;

    void makeFrame();
    void setCell(Coord where, char what);

    GameBoardArray brd;
};