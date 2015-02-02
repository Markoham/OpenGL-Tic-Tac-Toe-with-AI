#include "board.h"

// init game
Board::Board()
{
    // Create board
    this->board = new int*[3];

    for(int i = 0; i < 3; i++) {
        this->board[i] = new int[3];

        for(int j = 0; j < 3; j++)
        {
            this->board[i][j] = 0;
        }
    }
}

Board::~Board()
{

}

void Board::place(int row, int cell, int value)
{
    this->board[row][cell] = value;
}

// return board
int** Board::getBoard()
{
    return this->board;
}

// Check winner
int Board::checkWin(int *winner)
{
    return checkWin(board, winner);
}

// Check winner
int Board::checkWin(int **b, int *winner)
{
    int win = 0;
    // Check rows
    for(int i = 0; i < 3; i++)
    {
        if(b[i][0] == b[i][1] && b[i][1] == b[i][2] && b[i][0] != 0)
        {
            win = 1;
            *winner = b[i][0];
            break;
        }
    }
    // Check Columns
    for(int i = 0; i < 3; i++)
    {
        if(b[0][i] == b[1][i] && b[1][i] == b[2][i] && b[0][i] != 0)
        {
            win = 1;
            *winner = b[0][i];
            break;
        }
    }
    // Check Cross
    if(b[0][0] == b[1][1] && b[1][1] == b[2][2] && b[0][0] != 0)
    {
        win = 1;
        *winner = b[0][0];
    }
    if(b[2][0] == b[1][1] && b[1][1] == b[0][2] && b[2][0] != 0)
    {
        win = 1;
        *winner = b[2][0];
    }

    if(!win)
    {
        int draw = 1;
        for(int i = 0; i < 3; i++)
        {
            for(int j= 0; j < 3; j++)
            {
                if(b[i][j] == 0)
                {
                    draw = 0;
                    i = j = 3;
                }
            }
        }
        if(draw)
        {
            win = 1;
            *winner = 0;
        }
    }

    if(!win)
        *winner = 0;

    return win;
}

int Board::available(int row, int cell)
{
    return (this->board[row][cell] == 0);
}
