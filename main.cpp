#include "Game.hpp"

int main()
{
    srand(time(nullptr));

    Game game;
    game.levelMenu();
    game.refresh();

    while(!game.isOver)
    {
        game.makeAMove(game.getDirection());
        game.refresh();
        if(!game.applePlaced)
        {
            game.addApple();
        }
        ++game.turn;
    }
    std::cout << "GAME OVER!" << std::endl;
}