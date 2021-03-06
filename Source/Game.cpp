#include "Game.hpp"

void Game::levelMenu()
{
    isOver = false;
    board.initializeBoard();
    snake = {Coord(10,5), Coord(10,6)};
    turn = 0;
    score = 0;
    previousDirection = Up;
    bestScore = getBestScore();

    system("clear");

    std::cout << "Choose level:" << std::endl;
    std::cout << "1) Easy" << std::endl;
    std::cout << "2) Medium" << std::endl;
    std::cout << "3) Hard" << std::endl;

    switch(getch())
    {
        case '1':
            setLevel(Easy);
            break;
        case '2':
            setLevel(Medium);
            break;
        case '3':
            setLevel(Hard);
            break;
        default:
            levelMenu();
    }

    play();
}

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

void Game::makeAMove(const Direction dir)
{
    if((dir == Up && previousDirection == Down) || (dir == Down && previousDirection == Up) || (dir == Left && previousDirection == Right) || (dir == Right && previousDirection == Left))
    {
        makeAMove(getDirection());
    }
    else
    {
        unsigned nextX;
        unsigned nextY;
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

        if(board.checkAvailability(nextCoord) || (nextX == snake.back().x && nextY == snake.back().y))
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
                addApple();
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
    std::mt19937 rng(rd());
    std::uniform_int_distribution<unsigned> rand_X(1, board.BOARD_WIDTH - 1);
    std::uniform_int_distribution<unsigned> rand_Y(1, board.BOARD_HEIGHT - 1);

    unsigned randomX = rand_X(rng);
    unsigned randomY = rand_Y(rng);

    if(board.checkAvailability(Coord(randomX, randomY)))
    {
        if(checkIfNotDeadEnd(Coord(randomX, randomY)))
        {
            board.setApple(Coord(randomX, randomY));
        }
        else
        {
            addApple();
        }

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
    std::cout << "Use (W/A/S/D) to play" << std::endl;
    std::cout << "Turn: " << turn  << "   Score: " << score << "   Best score: " << bestScore << std::endl;
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
    return buf;
}

void Game::setLevel(const Level lvl)
{
    int wallsPlaced = 0;
    int wallsToBePlaced = 0;
    int randomX;
    int randomY;

    switch(lvl)
    {
        case Easy:
            wallsToBePlaced = 5;
            break;
        case Medium:
            wallsToBePlaced = 10;
            break;
        case Hard:
            wallsToBePlaced = 15;
            break;
    }

    while(wallsPlaced < wallsToBePlaced)
    {
        std::mt19937 rng(rd());
        std::uniform_int_distribution<unsigned> rand_X(1, board.BOARD_WIDTH - 1);
        std::uniform_int_distribution<unsigned> rand_Y(1, board.BOARD_HEIGHT - 1);

        randomX = rand_X(rng);
        randomY = rand_Y(rng);

        if(board.checkAvailability(Coord(randomX, randomY)))
        {
            board.setWall(Coord(randomX, randomY));
            ++wallsPlaced;
        }
    }

}

void Game::play()
{
    refresh();
    addApple();
    while(!isOver)
    {
        makeAMove(getDirection());
        refresh();
    }

   gameOver();
}

void Game::gameOver()
{
    system("clear");

    std::cout << "GAME OVER!" << std::endl;

    std::cout << "Score: " << score << std::endl;

    if(score > bestScore)
    {
        setBestScore(score);
        bestScore = score;
        std::cout << "NEW RECORD! ";
    }

    std::cout << "Best score: " << bestScore << std::endl << std::endl;

    std::cout << "Do you want to play again?" << std::endl;
    std::cout << "1. Yes" << std::endl;
    std::cout << "2. No" << std::endl;

    switch(getch())
    {
        case '1':
            levelMenu();
            break;
        case '2':
            exit(0);
        default:
            gameOver();
    }
}

int Game::getBestScore()
{
    int score;
    std::ifstream input("../Source/bestScore.score");
    if(input)
    {
        input >> score;
    }
    else
    {
       std::cout << "getBestScore: bestScore can't be found!" << std::endl;
       return 0;
    }
    input.close();
    return score;
}

void Game::setBestScore(const int scr)
{
    std::ofstream output("../Source/bestScore.score");
    if(output)
    {
        output << scr;
    }
    else
    {
        std::cout << "setBestScoreEver: bestScore can't be found!" << std::endl;
    }
    output.close();
}

bool Game::checkIfNotDeadEnd(const Coord where)
{
    int clearCells = 0;

    clearCells += board.checkAvailability(Coord(where.x + 1, where.y));
    clearCells += board.checkAvailability(Coord(where.x - 1, where.y));
    clearCells += board.checkAvailability(Coord(where.x, where.y + 1));
    clearCells += board.checkAvailability(Coord(where.x, where.y - 1));

    return (clearCells > 2);
}