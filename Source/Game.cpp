#include "Game.hpp"

Game::Direction Game::getDirection()
{
    char key;
    std::cin >> key;
    switch(toupper(key))
    {
        case 'W':
            return Up;
        case 'S':
            return Down;
        case 'A':
            return Left;
        case 'D':
            return Right;
        default:
            return getDirection();
    }
}

void Game::makeAMove(const Direction& dir)
{
    if((dir == Up && previousDirection == Down) || (dir == Down && previousDirection == Up) || (dir == Left && previousDirection == Right) || (dir == Right && previousDirection == Left))
    {
        makeAMove(getDirection());
    }
    else
    {
        int nextX;
        int nextY;
        switch(dir)
        {
                case Up:
                {
                    nextX = snake.front().x;
                    nextY = snake.front().y - 1;
                    break;
                }
                case Down:
                {
                    nextX = snake.front().x;
                    nextY = snake.front().y + 1;
                    break;
                }
                case Left:
                {
                    nextX = snake.front().x - 1;
                    nextY = snake.front().y;
                    break;
                }
                case Right:
                {
                    nextX = snake.front().x + 1;
                    nextY = snake.front().y;
                    break;
                }
        }

        Coord nextCoord(nextX, nextY);

        if(board.movePossible(nextCoord))
        {
            snake.push_front(nextCoord);
            if(!board.appleFound(nextCoord))
            {
                board.clearCell(Coord(snake.at(snake.size() - 1).x, snake.at(snake.size() - 1).y));
                snake.erase(snake.end());
            }
            else
            {
                ++score;
                applePlaced = false;
            }
            previousDirection = dir;
        }
        else
        {
            isOver = true;
        }
    }
}

void Game::addApple()
{
    board.setApple(Coord(rand() % (board.BOARD_WIDTH - 1) + 1, rand() % (board.BOARD_HEIGHT - 1) + 1));
    applePlaced = true;
}

void Game::refresh()
{
    board.putSnake(snake);
    board.printBoard();
    std::cout << "Turn:  " << turn << std::endl;
    std::cout << "Score: " << score << std::endl;
}