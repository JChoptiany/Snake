#pragma once

#include "Board.hpp"
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <termios.h>

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

    enum Level
    {
        Easy,
        Medium,
        Hard
    };

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
    char getch();
    void levelMenu();
    void setLevel(const Level& lvl);

    bool isOver;
    bool applePlaced;
    int turn;
    int score;
    Board board;
    SnakeBody snake{Coord(10,5), Coord(10,6)};
    Direction previousDirection;
};