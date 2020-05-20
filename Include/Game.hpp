#pragma once

#include "Board.hpp"
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <termios.h>
#include <fstream>

class Game
{
public:
    void levelMenu();

private:
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
    void setLevel(const Level& lvl);
    void play();
    void gameOver();
    int getBestScore();
    void setBestScore(const int& scr);
    bool checkIfNotDeadEnd(const Coord& where);

    Direction previousDirection;
    SnakeBody snake;
    int bestScore;
    bool isOver;
    int turn;
    int score;
    Board board;
};