#ifndef AI_H
#define AI_H

#include <iostream>
#include "game.h"

class Game;

class AI
{
public:
    AI();
    ~AI();
    void setGame(Game *g);
    void setInfo(int *t, int *r);
    void findBest(int *row, int *cell);
    int gameTree(int **b, int t, int r);

private:
    Game *game;
    int** createArray();
    int** copyArray(int **a);
};

#endif // AI_H
