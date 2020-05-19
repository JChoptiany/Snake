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
        srand(time(nullptr));
        applePlaced = false;
        turn = 0;
        score = 0;
        previousDirection = Up;
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
    void play();
    void gameOver();

    bool isOver;
    bool applePlaced;
    int turn;
    int score;
    Board board;
    SnakeBody snake;
    Direction previousDirection;
};