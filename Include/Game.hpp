#pragma once

#include "Board.hpp"
#include <random>
#include <unistd.h>
#include <termios.h>
#include <fstream>

class Game
{
public:
    void levelMenu();

private:
    std::random_device rd;

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
    void makeAMove(Direction dir);
    void addApple();
    void refresh();
    static char getch();
    void setLevel(Level lvl);
    void play();
    void gameOver();
    static int getBestScore();
    static void setBestScore(int scr);
    bool checkIfNotDeadEnd(Coord where);

    Direction previousDirection;
    SnakeBody snake;
    int bestScore;
    bool isOver;
    int turn;
    int score;
    Board board;
};