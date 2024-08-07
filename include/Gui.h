#pragma once
#include <imgui.h>

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Game.h"

class Gui
{

private:
    ImGuiIO *io;
    ImFont *font;
    Game *game;

public:
    Gui(GLFWwindow *window, Game *game, std::string assetspath);
    void NewFrame();
    void EndFrame();
    ImGuiIO *GetIO();
    Game* GetGame();
    ~Gui();
};