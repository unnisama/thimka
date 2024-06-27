#pragma once
#include <vertexbuffer.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <stdio.h>
#include "timer.h"
#include <string>
#include <iostream>
#include "callbackevents.h"

class Game
{
private:
    Timer timer;

public:
    Game(int WIDTH, int HEIGHT, const char *title);
    void HandleBufferAndEvent();
    bool ShouldClose();
    void EnableDebug();
    float Step();
    float GetTime();
    void ResizeCallBack(int width, int height);
    inline static GLFWwindow *GetWindow() { return window; };
    inline int GetWIDTH() const { return WIDTH; };
    inline int GetHEIGHT() const { return HEIGHT; };

    ~Game();
public:
    static int WIDTH;
    static int HEIGHT;
    static GLFWwindow *window;
};

