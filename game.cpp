#include "game.h"

Game::Game(Board *b, AI *a)
{
    this->turn = 1;
    this->rounds = 1;
    this->end = 0;

    this->board = b;
    this->ai = a;
}

Game::~Game()
{
    if(this->board)
        delete this->board;
    if(this->ai)
        delete this->ai;
}

void Game::update()
{

    if(this->turn == -1)
    {
        int row = 0, cell = 0;
        ai->findBest(&row, &cell);
        this->play(row, cell);
    }

    if(!this->isEnd())
    {
        if(this->checkWin(this->getBoard(), &winner))
        {
            if(winner == 1)
                std::cout << "Cross win game!" << std::endl;
            else if(winner == -1)
                std::cout << "Nought win game!" << std::endl;
            else
                std::cout << "Draw!" << std::endl;
            end++;
        }
    }
}

int** Game::getBoard()
{
    return board->getBoard();
}

// ensure that player cannot cheat
int Game::play(int row, int cell)
{
    int ok = 0;

    if(this->available(row, cell))
    {
        this->board->place(row,cell,this->turn);
        this->rounds++;
        this->turn *= -1;
        ok = 1;
    }

    return ok;
}

int Game::getTurn()
{
    return this->turn;
}

int Game::getRounds()
{
    return this->rounds;
}

int Game::isEnd()
{
    return this->end;
}

int Game::available(int row, int cell)
{
    return this->board->available(row, cell);
}

int Game::checkWin(int **b, int *winner)
{
    return this->board->checkWin(b, winner);
}
