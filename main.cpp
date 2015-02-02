#include "ai.h"
#include "board.h"
#include "game.h"
#include "engine.h"

int main()
{
    AI* ai = new AI();
    Board *board = new Board();
    Game *game = new Game(board, ai);
    ai->setGame(game);
    Engine::setGame(game);
    Engine::init();
    Engine::run();
}

