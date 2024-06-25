#pragma once
#include <vertexbuffer.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <stdio.h>
#include "timer.h"
#include <string>
#include <iostream>

class Game
{
private:
    int WIDTH;
    int HEIGHT;
    GLFWwindow *window;
    Timer timer;

public:
    Game(int WIDTH, int HEIGHT, const char *title);
    void HandleBufferAndEvent();
    bool ShouldClose();
    void EnableDebug();
    float Step();
    float GetTime();
    GLFWwindow *GetWindow();

    ~Game();
};

