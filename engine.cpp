#include "engine.h"

GLFWwindow* Engine::window;
int** Engine::board;
int Engine::row = 0;
int Engine::cell = 0;
Game *Engine::game;

void Engine::init()
{
    glfwSetErrorCallback(Engine::error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    Engine::window = glfwCreateWindow(WIDTH, HEIGHT, WINDOW_TITLE, NULL, NULL);
    if (!Engine::window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(Engine::window);
    glfwSwapInterval(1);
    glfwSetKeyCallback(Engine::window, Engine::key_callback);
    glfwSetCursorPosCallback(Engine::window, cursor_position_callback);
    glfwSetMouseButtonCallback(Engine::window, mouse_button_callback);
}

void Engine::setGame(Game *g)
{
    Engine::game = g;
}

void Engine::error_callback(int error, const char* description)
{
    std::cout << error << " " << description << std::endl;
}

void Engine::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(Engine::window, GL_TRUE);
}

void Engine::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    Engine::cell = (xpos/200.f);
    Engine::row = (ypos/200.f);
}

void Engine::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        if(Engine::game->getTurn() == 1 && !Engine::game->isEnd())
        {
            if(Engine::game->available(row, cell))
            {
                Engine::game->play(row, cell);
            }
        }
    }
}

int Engine::getMousePosRow()
{
    return Engine::row;
}

int Engine::getMousePosCell()
{
    return Engine::cell;
}

// Draw Nought
void Engine::drawNought(int row, int cell)
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
void Engine::drawCross(int row, int cell, int highlight)
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
void Engine::drawBoard(int **board)
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
                Engine::drawCross(i+1,j+1);
            else if(board[i][j] == -1)
                Engine::drawNought(i+1, j+1);
        }
    }

    if(Engine::game->available(row,cell) && !Engine::game->isEnd())
    {
        Engine::drawCross(row+1, cell+1, 1);
    }
}

void Engine::run()
{
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

        game->update();

        drawBoard(game->getBoard());
/*
        int winner;
        if(game->checkWin(board, &winner))
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
*/
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(Engine::window);
    glfwTerminate();

    exit(EXIT_SUCCESS);
}
