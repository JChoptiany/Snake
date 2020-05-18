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

    typedef std::array<std::array<char, BOARD_WIDTH>, BOARD_HEIGHT> GameBoardArray;

    void printBoard();
    void putSnake(const SnakeBody& snake);
    void initializeBoard();
    void clearCell(const Coord& where);
    void setApple(const Coord& where);
    bool movePossible(const Coord& where);
    bool appleFound(const Coord& where);

private:
    void makeFrame();
    void setCell(const Coord& where, const char& what);

    GameBoardArray brd;
};