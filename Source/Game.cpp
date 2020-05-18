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
        switch(dir)
        {
            case Up:
            {
                Coord upCoord(snake.front().x, snake.front().y - 1);
                if(board.movePossible(upCoord))
                {
                    snake.push_front(upCoord);
                    if (!board.appleFound(upCoord))
                    {
                        board.clearCell(Coord(snake.at(snake.size() - 1).x, snake.at(snake.size() - 1).y));
                        snake.erase(snake.end());
                    }
                    else
                    {
                        ++score;
                        applePlaced = false;
                    }
                    previousDirection = Up;
                }
                else
                {
                    isOver = true;
                }
                break;
            }
            case Down:
            {
                Coord downCoord(snake.front().x, snake.front().y + 1);
                if (board.movePossible(downCoord))
                {
                    snake.push_front(downCoord);
                    if (!board.appleFound(downCoord))
                    {
                        board.clearCell(Coord(snake.at(snake.size() - 1).x, snake.at(snake.size() - 1).y));
                        snake.erase(snake.end());
                    }
                    else
                    {
                        ++score;
                        applePlaced = false;
                    }
                    previousDirection = Down;
                }
                else
                {
                    isOver = true;
                }
                break;
            }
            case Left:
            {
                Coord leftCoord(snake.front().x - 1, snake.front().y);
                if (board.movePossible(leftCoord))
                {
                    snake.push_front(leftCoord);
                    if (!board.appleFound(leftCoord))
                    {
                        board.clearCell(Coord(snake.at(snake.size() - 1).x, snake.at(snake.size() - 1).y));
                        snake.erase(snake.end());
                    }
                    else
                    {
                        ++score;
                        applePlaced = false;
                    }
                    previousDirection = Left;
                }
                else
                {
                    isOver = true;
                }
                break;
            }
            case Right:
            {
                Coord rightCoord(snake.front().x + 1, snake.front().y);
                if (board.movePossible(rightCoord))
                {
                    snake.push_front(rightCoord);
                    if (!board.appleFound(rightCoord))
                    {
                        board.clearCell(Coord(snake.at(snake.size() - 1).x, snake.at(snake.size() - 1).y));
                        snake.erase(snake.end());
                    }
                    else
                    {
                        ++score;
                        applePlaced = false;
                    }
                    previousDirection = Right;
                } else
                {
                    isOver = true;
                }
                break;
            }
            default:
            {
                std::cout << "DIRECTION ERROR!";
                isOver = true;
            }
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
