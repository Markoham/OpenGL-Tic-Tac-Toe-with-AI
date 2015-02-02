#ifndef ENGINE_H
#define ENGINE_H

#include <GLFW/glfw3.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "game.h"
#include "settings.h"

class Engine
{
public:
    static void init();
    static void setGame(Game *g);
    static int getMousePosRow();
    static int getMousePosCell();
    static void setMouseClickCallback();
    static void run();

private:
    static void error_callback(int error, const char* description);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    static void drawNought(int row, int cell);
    static void drawCross(int row, int cell, int highlight = 0);
    static void drawBoard(int **board);
    static GLFWwindow* window;
    static int row;
    static int cell;
    static Game *game;
};

#endif // ENGINE_H
