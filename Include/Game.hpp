#pragma once

#include "Board.hpp"
#include <cstdlib>
#include <ctime>

class Game
{
public:
    Game()
    {
        isOver = false;
        applePlaced = false;
        turn = 0;
        score = 0;
        previousDirection = Up;
        board.initializeBoard();
    }

    enum Direction
    {
        Up,
        Down,
        Left,
        Right
    };

    Direction getDirection();
    void makeAMove(const Direction& dir);
    void addApple();
    void refresh();

    bool isOver;
    bool applePlaced;
    int turn;
    int score;
    Board board;
    SnakeBody snake{Coord(10,5), Coord(10,6)};
    Direction previousDirection;
};