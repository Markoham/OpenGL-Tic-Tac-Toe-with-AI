#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "ai.h"

class AI;

class Game
{
public:
    Game();
    Game(Board *b, AI *a);
    ~Game();
    void update();
    int **getBoard();
    int getTurn();
    int getRounds();
    int isEnd();
    int play(int row, int cell);
    int available(int row, int cell);
    int checkWin(int **b, int *winner);

private:
    Board *board;
    AI *ai;
    int turn;
    int rounds;
    int end;
    int winner;
};

#endif // GAME_H
