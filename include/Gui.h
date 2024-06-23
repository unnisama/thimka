#pragma once
#include <imgui.h>

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class Gui
{

private:
    ImGuiIO *io;
    ImFont *font;

public:
    Gui(GLFWwindow *window);
    void NewFrame();
    void DrawFrame();
    ImGuiIO *GetIO();
    ~Gui();
};