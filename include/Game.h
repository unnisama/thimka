#pragma once
#include <vertexbuffer.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <stdio.h>

class Game
{
private:
    int WIDTH;
    int HEIGHT;
    GLFWwindow *window;

public:
    Game(int WIDTH, int HEIGHT, const char *title);
    void HandleBufferAndEvent();
    bool ShouldClose();
    void SetDebug(GLDEBUGPROC callback);
    GLFWwindow *GetWindow();

    ~Game();
};

