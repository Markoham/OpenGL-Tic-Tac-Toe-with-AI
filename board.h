#ifndef BOARD_H
#define BOARD_H


class Board
{
public:
    Board();
    ~Board();
    void place(int row, int cell, int value);
    int** getBoard();
    int checkWin(int *winner);
    int checkWin(int **b, int *winner);
    int available(int row, int cell);

private:
    int **board;
};

#endif // BOARD_H
