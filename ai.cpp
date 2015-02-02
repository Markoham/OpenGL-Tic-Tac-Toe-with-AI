#include "ai.h"

AI::AI()
{

}

AI::~AI()
{

}

int** AI::createArray()
{
    int **tmp = new int*[3];

    for(int i = 0; i < 3; i++) {
        tmp[i] = new int[3];

        for(int j = 0; j < 3; j++)
        {
            tmp[i][j] = 0;
        }
    }

    return tmp;
}

int** AI::copyArray(int **a)
{
    int **tmp = new int*[3];

    for(int i = 0; i < 3; i++) {
        tmp[i] = new int[3];

        for(int j = 0; j < 3; j++)
        {
            tmp[i][j] = a[i][j];
        }
    }

    return tmp;
}

void AI::setGame(Game *g)
{
    this->game = g;
}

void AI::findBest(int *row, int *cell)
{
    // Best move board
    int **best = createArray();

    int **b = this->game->getBoard();

    // If first AI move
    if(this->game->getRounds() == 2)
    {
        if(b[0][0] == 1)
            best[1][1] += -100;
        else if(b[0][2] == 1)
            best[1][1] += -100;
        else if(b[2][0] == 1)
            best[1][1] += -100;
        else if(b[2][2] == 1)
            best[1][1] += -100;
        else if(b[1][1] == 0)
            best[1][1] += -100;
        else if(b[0][0] == 0)
            best[0][0] += -100;
    }
    else
    {
        // Check if player is winning
        for(int i = 0; i < 3; i++)
        {
            if(b[i][0] == b[i][1] && b[i][0] == 1)
                best[i][2] += -100;
            if(b[i][0] == b[i][2] && b[i][0] == 1)
                best[i][1] += -100;
            if(b[i][1] == b[i][2] && b[i][1] == 1)
                best[i][0] += -100;
        }
        for(int j = 0; j < 3; j++)
        {
            if(b[0][j] == b[1][j] && b[0][j] == 1)
                best[2][j] += -100;
            if(b[0][j] == b[2][j] && b[0][j] == 1)
                best[1][j] += -100;
            if(b[1][j] == b[2][j] && b[1][j] == 1)
                best[0][j] += -100;
        }
        if(b[0][0] == b[2][2] && b[0][0] == 1)
            best[1][1] += -100;
        if(b[0][0] == b[1][1] && b[0][0] == 1)
            best[2][2] += -100;
        if(b[2][0] == b[0][2] && b[2][0] == 1)
            best[1][1] += -100;
        if(b[2][0] == b[1][1] && b[2][0] == 1)
            best[0][2] += -100;
    }

    // Check if AI can win
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(b[i][j] == 0)
            {
                int **b2 = copyArray(b);
                b2[i][j] = -1;
                best[i][j] += gameTree(b2,(this->game->getTurn() * -1), (this->game->getRounds()+1));
            }
        }
    }

    // Find best move
    int bi = 0, bj = 0;
    int bv = 100;
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(best[i][j] < bv && b[i][j] == 0)
            {
                bv = best[i][j];
                bi = i;
                bj = j;
            }
        }
    }
    *row = bi;
    *cell = bj;
}

// Game tree logic
int AI::gameTree(int **b, int t, int r)
{
    int winner;
    int best = 1;

    if(this->game->checkWin(b, &winner))
    {
        if((this->game->getRounds()+1) == r && winner == -1)
            best += 10000;

        return best * winner;
    }

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(b[i][j] == 0)
            {

                int **b2 = copyArray(b);

                if(t == 1)
                    b2[i][j] = 1;
                else
                    b2[i][j] = -1;

                int result = gameTree(b2, (t * -1), (r+1));
                if(best > result)
                {
                    best += result;
                }
            }
        }
    }

    return best;
}
