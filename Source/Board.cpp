#include "Board.hpp"

void Board::printBoard()
{
    system("clear");
    for(int x = 0; x < BOARD_HEIGHT; x++)
    {
        for(int y = 0; y < BOARD_WIDTH; y++)
        {
            std::cout << brd[x][y];
        }
        std::cout << std::endl;
    }
}

void Board::putSnake(const SnakeBody& snake)
{
    for(auto bodyPart : snake)
    {
        setCell(bodyPart, 's');
    }
    setCell(snake.front(), 'S');
}

void Board::initializeBoard()
{
    for(int y = 1; y < BOARD_HEIGHT - 1; y++)
    {
        for(int x = 1; x < BOARD_WIDTH - 1; x++)
        {
            clearCell(Coord(x,y));
        }
    }
    makeFrame();
}

void Board::makeFrame()
{
    for(int y = 0; y < BOARD_HEIGHT; y++)
    {
        setCell(Coord(0, y), '#');
        setCell(Coord(BOARD_WIDTH - 1, y), '#');
    }

    for(int x = 0; x < BOARD_WIDTH; x++)
    {
        setCell(Coord(x, 0), '#');
        setCell(Coord(x, BOARD_HEIGHT - 1), '#');
    }
}

void Board::setCell(const Coord& where, const char& what)
{
    brd[where.y][where.x] = what;
}

void Board::clearCell(const Coord& where)
{
    setCell(where, ' ');
}

bool Board::checkAvailability(const Coord& where)
{
    return brd[where.y][where.x] != 's' && brd[where.y][where.x] != '#' && brd[where.y][where.x] != 'S';
}

void Board::setApple(const Coord& where)
{
    if(brd[where.y][where.x] == ' ')
    {
        setCell(where, '@');
    }
}

bool Board::appleFound(const Coord& where)
{
    return (brd[where.y][where.x] == '@');
}

void Board::setWall(const Coord &where)
{
    if(brd[where.y][where.x] == ' ')
    {
        setCell(where, '#');
    }
}
