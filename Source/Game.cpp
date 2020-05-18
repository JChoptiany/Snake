#include "Game.hpp"

Game::Direction Game::getDirection()
{
    char key;
    key = getch();
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

        if(board.checkAvailability(nextCoord))
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
    int randomX = rand() % (board.BOARD_WIDTH - 1) + 1;
    int randomY = rand() % (board.BOARD_HEIGHT - 1) + 1;
    if(board.checkAvailability(Coord(randomX, randomY)))
    {
        board.setApple(Coord(randomX, randomY));
        applePlaced = true;
    }
    else
    {
        addApple();
    }
}

void Game::refresh()
{
    board.putSnake(snake);
    board.printBoard();
    std::cout << "Turn:  " << turn << std::endl;
    std::cout << "Score: " << score << std::endl;
}

char Game::getch(void)
{
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if(tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if(tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if(read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if(tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    printf("%c\n", buf);
    return buf;
}