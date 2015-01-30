#include <iostream>
#include <string.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <unistd.h>

#define WIDTH				600
#define HEIGHT				600
#define WINDOW_TITLE		"Tic-Tac-Toe"
#define CLEAR_COLOR			0, 0, 0, 0
#define DRAW_COLOR			1.0, 1.0, 1.0

int board[3][3] = {{0,0,0}, {0,0,0}, {0,0,0}};

int turn = 1;
int rounds = 1;
int end = 0;

// Debug console board
void printBoard(int b[3][3])
{
    std::cout << b[0][0] << "|" << b[0][1] << "|" << b[0][2] << std::endl;
    std::cout << "-------" << std::endl;
    std::cout << b[1][0] << "|" << b[1][1] << "|" << b[1][2] << std::endl;
    std::cout << "-------" << std::endl;
    std::cout << b[2][0] << "|" << b[2][1] << "|" << b[2][2] << std::endl;
}

// Check if move is allowed
int play(int row, int cell)
{
    int ok = 0;

    if(board[row][cell] == 0)
    {
        board[row][cell] = turn;
        rounds++;
        turn *= -1;
        ok = 1;
    }

    return ok;
}

// Check winner
int checkWin(int b[3][3], int *winner)
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


// #########################
// ########## AI ###########
// #########################

// Game tree logic
int gameTree(int b[3][3], int t, int r)
{
    int winner;
    int best = 1;

    if(checkWin(b, &winner))
    {
        if((rounds+1) == r && winner == -1)
            best += 10000;

        return best * winner;
    }

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(b[i][j] == 0)
            {

                int b2[3][3];
                std::copy(&b[0][0], &b[0][0] + 3*3, &b2[0][0]);

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

void ai()
{
    if(turn == 1)
        return;

    // Best move board
    int best[3][3] = {{0,0,0},{0,0,0},{0,0,0}};

    // If first AI move
    if(rounds == 2)
    {
        if(board[0][0] == 1)
            best[2][2] += -100;
        else if(board[0][2] == 1)
            best[2][0] += -100;
        else if(board[2][0] == 1)
            best[0][2] += -100;
        else if(board[2][2] == 1)
            best[0][0] += -100;
        else if(board[2][2] == 0)
            best[2][2] += -100;
    }
    else
    {
        // Check if player is winning
        for(int i = 0; i < 3; i++)
        {
            if(board[i][0] == board[i][1] && board[i][0] == 1)
                best[i][2] += -100;
            if(board[i][0] == board[i][2] && board[i][0] == 1)
                best[i][1] += -100;
            if(board[i][1] == board[i][2] && board[i][1] == 1)
                best[i][0] += -100;
        }
        for(int j = 0; j < 3; j++)
        {
            if(board[0][j] == board[1][j] && board[0][j] == 1)
                best[2][j] += -100;
            if(board[0][j] == board[2][j] && board[0][j] == 1)
                best[1][j] += -100;
            if(board[1][j] == board[2][j] && board[1][j] == 1)
                best[0][j] += -100;
        }
        if(board[0][0] == board[2][2] && board[0][0] == 1)
            best[1][1] += -100;
        if(board[0][0] == board[1][1] && board[0][0] == 1)
            best[2][2] += -100;
        if(board[2][0] == board[0][2] && board[2][0] == 1)
            best[1][1] += -100;
        if(board[2][0] == board[1][1] && board[2][0] == 1)
            best[0][2] += -100;
    }

    // Check if AI can win
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(board[i][j] == 0)
            {
                int b[3][3]; // copy board[3][3]
                std::copy(&board[0][0], &board[0][0] + 3*3, &b[0][0]);
                b[i][j] = -1;
                best[i][j] += gameTree(b,(turn * -1), (rounds+1));
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
            if(best[i][j] < bv && board[i][j] == 0)
            {
                bv = best[i][j];
                bi = i;
                bj = j;
            }
        }
    }

    if(!play(bi, bj))
    {
        std::cout << "ERROR!!" << std::endl;
    }
}

// Callbacks (Keyboars ans mouse)

void error_callback(int error, const char* description)
{
    std::cout << error << " " << description << std::endl;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

int row = 0, cell = 0;
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    cell = (xpos/200.f);
    row = (ypos/200.f);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        if(turn == 1 && !end)
        {
            if(board[row][cell] == 0)
            {
                play(row, cell);
            }
        }
    }
}

// #########################
// ######## OpenGL #########
// #########################

// Draw Nought
void drawNought(int row, int cell)
{
    float centerX = (cell/3.f) - (1.f/6.f);
    float centerY = (row/3.f) - (1.f/6.f);

    glColor3f(0.f, 0.f, 1.f);
    double angle = 2* 3.14/20 ;
    glBegin(GL_LINE_LOOP);
        double angle1=0.0;
        glVertex2d( centerX + cos(0.0)/12, centerY + sin(0.0)/12);
        int i;
        for ( i=0 ; i< 20 ;i++)
        {
            glVertex2d(centerX + cos(angle1)/12, centerY + sin(angle1)/12);
            angle1 += angle ;
        }
    glEnd();
    glFlush();
}

// Draw Cross
void drawCross(int row, int cell, int highlight = 0)
{
    float centerX = (cell/3.f) - (1.f/6.f);
    float centerY = (row/3.f) - (1.f/6.f);

    if(highlight) glColor3f(0.f, 1.f, 0.f);
    else glColor3f(1.f, 0.f, 0.f);
    glBegin(GL_LINES);
        glVertex3f(centerX - (1.f/12.f), centerY - (1.f/12.f), 0.f);
        glVertex3f(centerX + (1.f/12.f), centerY + (1.f/12.f), 0.f);
    glEnd();
    glBegin(GL_LINES);
        glVertex3f(centerX - (1.f/12.f), centerY + (1.f/12.f), 0.f);
        glVertex3f(centerX + (1.f/12.f), centerY - (1.f/12.f), 0.f);
    glEnd();
}

// Draw Board
void drawBoard()
{
    glBegin(GL_LINES);
        glColor3f(1.f, 1.f, 1.f);
        glVertex3f(0.f, (1.f/3.f), 0.f);
        glVertex3f(1.f, (1.f/3.f), 0.f);
    glEnd();

    glBegin(GL_LINES);
        glColor3f(1.f, 1.f, 1.f);
        glVertex3f(0.f, (2.f/3.f), 0.f);
        glVertex3f(1.f, (2.f/3.f), 0.f);
    glEnd();

    glBegin(GL_LINES);
        glColor3f(1.f, 1.f, 1.f);
        glVertex3f((1.f/3.f), 0.f, 0.f);
        glVertex3f((1.f/3.f), 1.f, 0.f);
    glEnd();

    glBegin(GL_LINES);
        glColor3f(1.f, 1.f, 1.f);
        glVertex3f((2.f/3.f), 0.f, 0.f);
        glVertex3f((2.f/3.f), 1.f, 0.f);
    glEnd();

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(board[i][j] == 1)
                drawCross(i+1,j+1);
            else if(board[i][j] == -1)
                drawNought(i+1, j+1);
        }
    }

    if(board[row][cell] == 0 && !end)
    {
        drawCross(row+1, cell+1, 1);
    }
}

// Main loop
int main()
{
    GLFWwindow* window;

    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    window = glfwCreateWindow(WIDTH, HEIGHT, WINDOW_TITLE, NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    while (!glfwWindowShouldClose(window))
    {
        int width, height;

        glfwGetFramebufferSize(window, &width, &height);

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0.f, 1.f, 1.f, 0.f, -1.f, 1.f);
        glMatrixMode(GL_MODELVIEW);

        glLoadIdentity();

        drawBoard();

        int winner;
        if(checkWin(board, &winner))
        {
            if(!end)
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
        if(!end) ai();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    exit(EXIT_SUCCESS);
}

